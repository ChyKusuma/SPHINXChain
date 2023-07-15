# SPHINXBlock

## Introduction

This project is dedicated to the world community as an Open-source Post-quantum blockchain layer 1 project, means anyone can join and contribute based on his/ her passion and skills. SPHINX is a blockchain protocol designed to provide secure and scalable solutions in the post-quantum era.

This repository contains code for the SPHINXChain project, which is a `Chain` module for the SPHINX blockchain framework.

## Components

### Namespace Declarations

The code starts with several namespace declarations:

- The `SPHINXBlock` namespace contains the `Block` class.
- The `SPHINXHash` namespace contains the `SPHINX_256` function.
- The `SPHINXTrx` namespace contains the `SPHINXTrx` function.

### Class Declaration: Chain

The `Chain` class represents a chain in the SPHINX network. It provides the following member functions:

#### Bridge

The bridge functionality allows communication and interaction between different chains in the SPHINX network. It enables the transfer of assets and transactions between chains. The `Chain` class provides the following functions related to bridges:

- `createBlockchainBridge`: This function creates a bridge between the current chain and a target chain. It establishes a connection between the two chains, enabling the transfer of assets and transactions.
- `handleBridgeTransaction`: This function handles a transaction originating from a bridge. It receives and processes bridge transactions within the target chain, ensuring proper execution and synchronization of data.

#### Horizontal Shard

Horizontal sharding involves dividing a blockchain network into multiple shards, with each shard responsible for processing a subset of transactions. The `Chain` class includes functions to manage shards and perform transactions within them:

- `createShard`: This function creates a new shard with the given name. It sets up a separate shard within the chain, allowing specific transactions to be processed independently.
- `joinShard`: This function joins the current chain to an existing shard with the given name. It facilitates communication and transaction processing between the main chain and the specified shard.
- `transferToShard`: This function transfers funds from the main chain to a specific shard. It enables users to move their assets from the main chain to a particular shard, promoting scalability and efficiency.
- `handleShardTransfer`: This function handles a transfer transaction within a shard. It processes transfers occurring within a shard and updates the respective balances accordingly.
- `handleShardBridgeTransaction`: This function handles a bridge transaction within a shard. It manages transactions originating from a bridge that involve the shard, ensuring proper execution and data synchronization.

#### Swap Function

The Chain class includes the `performAtomicSwap` function, which enables atomic swaps between chains. Atomic swaps allow two parties to exchange assets from different chains without the need for a trusted third party. The `performAtomicSwap` function facilitates secure and trustless asset exchanges between chains within the SPHINX network.

#### Other Features

In addition to the above features, the Chain class offers various functionalities to manage blocks, handle transactions, and maintain the chain's state. Some notable features include:

- Block Management: The Chain class provides functions like `addBlock`, `getBlockHash`, `getGenesisBlock`, `getBlockAt`, and `getChainLength` to manage blocks within the chain. These functions allow adding new blocks, retrieving block information, and interacting with the chain's block structure.
- Serialization and Persistence: The `toJson` and `fromJson` functions allow the serialization and deserialization of chain data in JSON format. The `save` and `load` functions enable saving and loading chain data to and from a file, ensuring the persistence of chain information across different sessions.
- Transaction Handling: The Chain class includes functions like `signTransaction`, `broadcastTransaction`, `updateBalance`, `getBalance`, and `verifyAtomicSwap` to handle various types of transactions within the chain. These functions facilitate transaction signing, broadcasting, balance management, and verification.
- Visualization: The `visualizeChain` function prints a visualization of the chain, providing a graphical representation of the blocks and their relationships. This feature aids in understanding the structure and state of the chain.

These features collectively contribute to the functionality, scalability, and interoperability of the SPHINX network, enabling bridges between chains, horizontal sharding, atomic swaps, efficient transaction processing, and data management within and between chains.

### Member Function Definitions

After the class declaration, the code defines the member functions of the Chain class. Each function is implemented with its respective functionality.


### This repository is part of the  [SPHINXPoW](https://github.com/SPHINX-HUB-ORG/SPHINXPoW) [SPHINXMiner](https://github.com/SPHINX-HUB-ORG/SPHINXMINER) [SPHINXBlock](https://github.com/SPHINX-HUB-ORG/SPHINXBLOCK)

Please note that the code in this repository is a part of the SPHINX blockchain algorithm, which is currently in development and not fully integrated or extensively tested for functionality. The purpose of this repository is to provide a framework and algorithm for SPHINX "Chain" blockchain project.

As the project progresses, further updates and enhancements will be made to ensure the code's stability and reliability. We encourage contributors to participate in improving and refining the SPHINXBlock algorithm by submitting pull requests and providing valuable insights.

We appreciate your understanding and look forward to collaborative efforts in shaping the future of the SPHINX blockchain project.

## Getting Started
To get started with the SPHINX blockchain project, follow the instructions below:

1. Clone the repository: `git clone https://github.com/ChyKusuma/SPHINXChain.git`
2. Install the necessary dependencies (List the dependencies or provide a link to the installation guide).
3. Explore the codebase to understand the project structure and components.
4. Run the project or make modifications as needed.


## Contributing
We welcome contributions from the developer community to enhance the SPHINX blockchain project. If you are interested in contributing, please follow the guidelines below:

1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix: `git checkout -b feature/your-feature-name` or `git checkout -b bugfix/your-bug-fix`.
3. Make your modifications and ensure the code remains clean and readable.
4. Write tests to cover the changes you've made, if applicable.
5. Commit your changes: `git commit -m "Description of your changes"`.
6. Push the branch to your forked repository: `git push origin your-branch-name`.
7. Open a pull request against the main repository, describing your changes and the problem it solves.
8. Insert your information (i.e name, email) in the authors space.

## License
Specify the license under which the project is distributed (MIT License).

## Contact
If you have any questions, suggestions, or feedback regarding the SPHINX blockchain project, feel free to reach out to us at [sphinxfounders@gmail.com](mailto:sphinxfounders@gmail.com).
