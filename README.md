# Basic Blockchain Implementation

## Project Overview
This project is a basic implementation of a blockchain using C++ named **IronBlock**. It demonstrates fundamental blockchain concepts, including blocks, transactions, hashing, and basic state management. The primary components of the project are:

- **Blocks** that store data, previous hash information, and timestamps.
- **Transaction Management** for updating balances and validating transactions.
- **Hashing** for ensuring the integrity of block data.

The code is modular, divided into different classes and functions that make it easy to understand how blocks interact within a blockchain.

## Files Overview

### Source Files
1. **src/main.cpp**: This file contains the main entry point of the application. It initializes the blockchain, demonstrates serialization of transaction data, and manages the creation of new blocks and transactions.

### Header Files
1. **include/block.h**: Defines the `Block` class that represents a block in the blockchain. Each block contains data such as index, previous block hash, and timestamp. It also includes functionality for hashing using the Sodium library.

2. **include/blockOperation.h**: Defines helper functions related to block operations, such as creating transactions, updating the state, and validating transactions. This helps in managing the transactions effectively within the blockchain.

3. **include/utility.h**: Contains utility functions for serialization of various data types. The serialization is used to convert data into a form suitable for hashing.

### CMake Configuration
- **CMakeLists.txt**: Contains the build configuration for the project. It defines the compiler version, sets the C++ standard to C++17, and includes necessary dependencies such as `libsodium`.

## Prerequisites

- **CMake** 3.16 or higher
- **libsodium** for cryptographic functions
- **C++17** compatible compiler

## Building the Project
To build the project, make sure you have installed `libsodium` and CMake. Follow these steps:

1. Clone the repository.
2. Navigate to the project directory.
3. Run the following commands to build the project:

   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage
After successfully building the project, you can run the executable:

```sh
./basic_block_chain
```

### Example Output
The program creates a series of transactions, hashes data, and outputs serialized data along with generated block hashes. This demonstrates the process of maintaining a blockchain with validated transactions and the integrity provided by hash functions.

## Main Functionalities
- **Block Creation**: Blocks are created with an index, data, and reference to the previous hash.
- **Transaction Generation**: Generates transactions between users and updates the state.
- **Serialization**: Converts data structures to string format for hashing.
- **Hashing**: Uses Sodium cryptographic library to hash the contents of blocks.

## Key Concepts
- **Hashing**: The use of cryptographic hash functions (libsodium) to secure the contents of each block.
- **Transaction Validation**: Ensuring all transactions conserve balances and that no accounts go into negative states.
- **Serialization**: Helper functions to convert different data types to string format for processing.

## Dependencies
- **libsodium**: Used for cryptographic operations to secure the data in each block.
- **CMake**: To manage the project build system.

## Notes
- This project is meant for educational purposes, demonstrating blockchain principles.
- It is a basic implementation and should not be used for real-world financial transactions.

## Future Improvements
- **Persistent Storage**: Add support for saving blockchain data to files or a database.
- **Networking**: Implement a peer-to-peer networking module for block propagation.
- **Enhanced Security**: Add digital signatures for transaction authenticity.

## Author
Vineet Pandey

Feel free to contribute to this project or report any issues!

## License
This project is open source and available under the [MIT License](LICENSE).

