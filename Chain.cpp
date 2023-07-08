/*
 *  Copyright (c) (2023) SPHINX_ORG
 *  Authors:
 *    - (C kusuma) <thekoesoemo@gmail.com>
 *      GitHub: (https://github.com/chykusuma)
 *  Contributors:
 *    - (Contributor 1) <email1@example.com>
 *      Github: (https://github.com/yourgit)
 *    - (Contributor 2) <email2@example.com>
 *      Github: (https://github.com/yourgit)
 */


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// This code represents a portion of a blockchain implementation using the SPHINX blockchain framework. The code into its components and explain their functionality:

  // Chain::Chain(): This is the constructor of the Chain class. It creates the blockchain by initializing the genesis block. The genesis block is the first block in the blockchain and serves as the starting point.

  // Chain::addBlock(const SPHINXBlock& block): This function is responsible for adding a new block to the blockchain. It takes a SPHINXBlock object as a parameter, representing the block to be added. The function calculates the hash of the block's data, signs the block's hash using a private key, and adds the block and its signature to the chain.

  // Chain::isChainValid() const: This function validates the integrity of the blockchain. It iterates through the blocks in the blockchain, starting from the second block, and verifies the consistency of each block. It checks if the block's calculated hash matches the actual hash computed from the block's data and verifies the block's signature. If any discrepancy is found, the function returns false, indicating that the chain is invalid. If all blocks pass the verification checks, the function returns true, indicating that the chain is valid.

  // Chain::getGenesisBlock() const: This function retrieves the genesis block, which is the first block in the blockchain. It returns the first element of the blocks_ vector.

  // Chain::getBlockAt(size_t index) const: This function retrieves a block at a specified index in the blockchain. It takes an index as a parameter and returns the corresponding block from the blocks_ vector. If the index is out of range, it throws an out_of_range exception.

  // Chain::getChainLength() const: This function returns the length or size of the chain, which is the number of blocks in the blockchain. It simply returns the size of the blocks_ vector.

  // Chain::visualizeChain() const: This function visualizes the blockchain for analysis or presentation purposes. It iterates through the blocks in the blocks_ vector and prints information about each block. The specific details printed or displayed can be customized according to requirements.

  // Chain::toJson() const: This function serializes the blockchain into a JSON format. It creates a JSON object and populates it with an array of JSON representations of each block in the blockchain. The toJson function of each SPHINXBlock object is called to convert the block to JSON format.

  // Chain::fromJson(const json& chainJson): This function deserializes the blockchain from a JSON format. It takes a JSON object as a parameter, representing the serialized blockchain. The function clears the existing blocks_ vector and iterates through the JSON array of blocks. For each block, a new SPHINXBlock object is created and initialized using the fromJson function, and the block is added to the blocks_ vector. If the JSON structure is invalid or contains missing fields, it throws an invalid_argument exception.

  // The SPHINX_Chain namespace encapsulates the blockchain-related functionality, including block addition, validation, retrieval, visualization, and serialization/deserialization. It uses the SPHINXBlock class, which represents individual blocks in the blockchain. The SPHINXSign and SPHINXVerify namespaces are used for block signing and verification processes, respectively.
/////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <array>
#include <iostream>
#include <string>
#include "Chain.hpp"
#include "json.hpp"
#include "Block.hpp"
#include "Verify.hpp"
#include "Sign.hpp"

using json = nlohmann::json;


namespace SPHINX_Chain {

    Chain::Chain() {
        // Create the genesis block with the provided message
        std::string genesisMessage = "Welcome to Post-Quantum era, The Beginning of a Secured-Trustless Economy will start from here - SPHINX Blockchain Genesis";
        SPHINXBlock genesisBlock(genesisMessage);

        // Add the genesis block to the chain
        blocks_.push_back(genesisBlock);
    }

    void Chain::addBlock(const SPHINXBlock& block) {
        // Add block to the blockchain
        // Calculate the hash of the block's data
        std::string blockHash = block.calculateBlockHash();

        // Sign the block's hash using the private key
        std::string signature = SPHINXSign::sign(blockHash, privateKey_);

        // Add the block and its signature to the chain
        blocks_.emplace_back(block, signature);
    }

    bool Chain::isChainValid() const {
        // Validate the integrity of the blockchain
        for (size_t i = 1; i < blocks_.size(); ++i) {
            const SPHINXBlock& currentBlock = blocks_[i];
            const SPHINXBlock& previousBlock = blocks_[i - 1];

            // Verify the block's hash and previous block hash
            if (currentBlock.getBlockHash() != currentBlock.calculateBlockHash() ||
                currentBlock.getPreviousHash() != previousBlock.calculateBlockHash()) {
                return false;
            }

            // Verify the signature of the block
            if (!SPHINXVerify::verifySPHINXBlock(currentBlock, currentBlock.getSignature(), publicKey_)) {
                return false;
            }
        }

        return true;
    }

    SPHINXBlock Chain::getGenesisBlock() const {
        // Get the first block in the blockchain
        return blocks_.front();
    }

    SPHINXBlock Chain::getBlockAt(size_t index) const {
        // Get the block at the specified index
        if (index < blocks_.size()) {
            return blocks_[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    size_t Chain::getChainLength() const {
        // Get the length or size of the chain
        return blocks_.size();
    }

    void Chain::visualizeChain() const {
        // Visualize the blockchain for analysis or presentation purposes
        for (size_t i = 0; i < blocks_.size(); ++i) {
            const SPHINXBlock& block = blocks_[i];
            std::cout << "Block " << i << " - Hash: " << block.getBlockHash() << std::endl;
            // Print or display other block details as desired
        }
    }

    // Serialize the chain to JSON
    json Chain::toJson() const {
        json chainJson;
        chainJson["blocks"] = json::array();
        for (const SPHINXBlock& block : blocks_) {
            chainJson["blocks"].push_back(block.toJson());
        }
        return chainJson;
    }

    // Deserialize the chain from JSON
    void Chain::fromJson(const json& chainJson) {
        blocks_.clear();
        if (chainJson.contains("blocks") && chainJson["blocks"].is_array()) {
            const json& blocksJson = chainJson["blocks"];
            for (const json& blockJson : blocksJson) {
                SPHINXBlock block;
                block.fromJson(blockJson);
                blocks_.push_back(block);
            }
        } else {
            throw std::invalid_argument("Invalid JSON structure or missing fields");
        }
    }
} // namespace SPHINX_Chain