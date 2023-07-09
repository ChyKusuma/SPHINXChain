# SPHINXBlock

## Introduction

This project is dedicated to the world community as an Open-source Post-quantum SPHINXChain blockchain, means anyone can join and contribute based on his/ her passion and skills. SPHINX is a blockchain protocol designed to provide secure and scalable solutions in the post-quantum era.

This repository contains code for the SPHINXChain project, which is a `Block` module for the SPHINX blockchain framework. The SPHINXChain aims to provide a "Chain" in the blockchain systems.


## Components

### SPHINX_Chain Namespace

This code represents the implementation of the `SPHINX_Chain` namespace, which includes the `Chain` class responsible for managing the blockchain. Let's break down the important components and their functions:

- `Chain::Chain()`: This is the constructor for the `Chain` class. It creates a genesis block with a predefined message and adds it to the chain.

- `Chain::addBlock(const SPHINXBlock& block)`: This function adds a new block to the blockchain. It calculates the hash of the block's data, signs the hash using the private key, and adds the block along with its signature to the chain.

- `Chain::isChainValid() const`: This function validates the integrity of the blockchain. It iterates through each block in the chain, starting from the second block, and verifies the block's hash and previous block hash. It also verifies the signature of each block. If any inconsistency or invalid signature is found, it returns `false`; otherwise, it returns `true`.

- `Chain::getGenesisBlock() const`: This function returns the genesis block, which is the first block in the blockchain.

- `Chain::getBlockAt(size_t index) const`: This function returns the block at the specified index in the blockchain. It checks if the index is within the valid range and throws an exception if it's out of range.

- `Chain::getChainLength() const`: This function returns the length or size of the blockchain, which is the number of blocks in the chain.

- `Chain::visualizeChain() const`: This function visualizes the blockchain for analysis or presentation purposes. It iterates through each block in the chain and prints the block index, hash, and any other desired details.

- `Chain::toJson() const`: This function serializes the blockchain into a JSON format. It creates a JSON object called `chainJson` and adds an array called "blocks" to it. It then iterates through each block in the chain, converts each block to its JSON representation using the `toJson()` function of the block, and adds it to the "blocks" array. Finally, it returns the `chainJson` object.

- `Chain::fromJson(const json& chainJson)`: This function deserializes the blockchain from a JSON format. It takes a JSON object called `chainJson` as input, representing the serialized blockchain. It clears the existing blocks in the chain and checks if the `chainJson` object contains the "blocks" key and if its value is an array. If these conditions are met, it retrieves the JSON array of blocks, iterates through each block JSON object, creates a new `SPHINXBlock` object, initializes it from the JSON using the `fromJson()` function of the block, and adds it to the chain. If the JSON structure is invalid or the required fields are missing, it throws an exception.

These components work together to provide functionality for initializing, modifying, validating, and visualizing the blockchain, as well as serializing and deserializing it from/to JSON format.

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
