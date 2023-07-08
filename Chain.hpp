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



#ifndef CHAIN_HPP
#define CHAIN_HPP

#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include "Block.hpp"
#include "Verify.hpp"
#include "json.hpp"
#include "Contract.hpp"


using json = nlohmann::json;

namespace SPHINX_Chain {

    class Chain {
    public:
        Chain();

        void addBlock(const SPHINXBlock& block);

        bool isChainValid() const;

        SPHINXBlock getGenesisBlock() const;

        SPHINXBlock getBlockAt(size_t index) const;

        size_t getChainLength() const;

        void visualizeChain() const;

        json toJson() const;

        void fromJson(const json& chainJson);

    private:
        std::vector<SPHINXBlock> blocks_;
        SPHINX_PublicKey publicKey_;
        SPHINX_PrivateKey privateKey_;
    };

    // Implementation of the member functions

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

    json Chain::toJson() const {
        json chainJson;
        chainJson["blocks"] = json::array();
        for (const SPHINXBlock& block : blocks_) {
            chainJson["blocks"].push_back(block.toJson());
        }
        return chainJson;
    }

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

#endif // SPHINX_CHAIN_HPP