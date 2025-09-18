#ifndef __CRC32RK_H
#define __CRC32RK_H

#include "Particle.h"

/**
 * @brief Class to calculate CRC32 (32-bit Cyclic Redundancy Check)
 * 
 * It uses the polynomial and other parameters as in gzip. If you need a node.js
 * version, see the [crc](https://www.npmjs.com/package/crc) package in NPM.
 */
class CRC32_RK {
public:
    /**
     * @brief Class to allow calculation across multiple buffers
     * 
     * Call the calculate() method to add a buffer. Returns the CRC to that point.
     * 
     * See also the static calculate() method in the CRC32_RK class that does not require creating a 
     * State object.
     */
    class State {
    public:
        /**
         * @brief Construct the State object for holding the CRC state
         */
        State() {};

        /**
         * @brief Destructor. This object does not have any externally allocated data and the destructor is trivial.
         */
        virtual ~State() {};

        /**
         * @brief Calculate the CRC32 for a buffer of data
         * 
         * @param buf Pointer to a buffer to calculate the CRC for. Cannot be null.
         * @param len The length of the buffer in bytes
         * @return uint32_t The CRC32 of the data thus far
         * 
         * The State object contains the current CRC32 being calculated. You can call calculate
         * multiple times on a single State instance to calculate the CRC for the entire data
         * in chunks.
         */
        uint32_t calculate(const unsigned char *buf, size_t len);

        /**
         * @brief Clear the state to be the same as when a new object is created
         */
        void clear() {
            crc = 0xffffffff;
        }

        /**
         * @brief Copies the state from another object during construction
         * 
         * @param other 
         */
        State(const State &other) { *this = other; };

        /**
         * @brief Copy the state from another object into this object
         * 
         * @param other 
         * @return State& 
         */
        State &operator=(const State &other) { crc = other.crc; return *this; };

        /**
         * @brief Returns true if this object and other have the same CRC state.
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool operator==(const State &other) const { return crc == other.crc; };

    protected:
        uint32_t crc = 0xffffffff; //!< The current CRC state. This is not the same as the result from calculate!
    };

    /**
     * @brief Calculate the CRC32 for a single buffer of data
     * 
     * @param buf Pointer to a buffer to calculate the CRC for. Cannot be null.
     * @param len The length of the buffer in bytes
     * @return uint32_t The CRC32 of the data
     */
    static uint32_t calculate(const unsigned char *buf, size_t len);
};

#endif // __CRC32RK_H
