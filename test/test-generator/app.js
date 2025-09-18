
const crc32 = require('crc/crc32'); // https://www.npmjs.com/package/crc

const testParams = [
    { size: 1, text: true, },
    { size: 10, text: true, },
    { size: 100, text: false, },
    { size: 500, text: false, },
    { size: 1500, text: false, },
];


function generateTestVector(options) {
    let result = {
        codeData: [],
        codeEntry: [],
    };

    let bytes = [];

    for(let ii = 0; ii < options.size; ii++) {
        if (options.text) {
            bytes[ii] = 32 + Math.floor(Math.random() * 95);
        }
        else {
            bytes[ii] = Math.floor(Math.random() * 256);
        }
    }
    // console.log('bytes', bytes);

    const buf = Buffer.alloc(options.size);
    for(let ii = 0; ii < options.size; ii++) {
        buf.writeUint8(bytes[ii], ii);
    }

    result.crc = '00000000' + crc32(buf).toString(16);
    result.crc = '0x' + result.crc.substring(result.crc.length - 8);

    result.codeData.push('// ' + JSON.stringify(options));    
    result.codeData.push('static const unsigned char _testData' + options.index + '[' + options.size + '] = {')
    let line = '    ';
    for(let ii = 0; ii < options.size; ii++) {
        let hex = '00' + buf.readUint8(ii).toString(16);
        hex = '0x' + hex.substring(hex.length - 2);
        line += hex;

        if ((ii % 16) == 15) {
            if ((ii + 1) < options.size) {
                line += ','
            }
            result.codeData.push(line);
            line = '    ';
        }
        else {
            if ((ii + 1) < options.size) {
                line += ', ';
            }
        }
    }
    if (line.trim().length) {
        result.codeData.push(line);
    }
    result.codeData.push('};');


    result.codeEntry.push('    { _testData' + options.index + ', ' + options.size + ', ' + result.crc + "},");

    return result;    
}

async function run() {
    let testVectors = [];

    for(const testParam of testParams) {
        testParam.index = testVectors.length;
        let result = generateTestVector(testParam);
        testVectors.push(result);
    }

    for(const testVector of testVectors) {
        console.log(testVector.codeData.join('\n'));        
    }
    console.log('const TestVector tests[] = {');
    for(const testVector of testVectors) {
        console.log(testVector.codeEntry.join('\n'));        
    }
    console.log('    { nullptr, 0, 0 }');
    console.log('};');
}

run();
