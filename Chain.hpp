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



#ifndef SPHINXCHAIN_HPP
#define SPHINXCHAIN_HPP

#pragma once

#include <stdexcept>
#include <fstream>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "Params.hpp"
#include "json.hpp"
#include "Block.hpp"
#include "Verify.hpp"
#include "Sign.hpp"
#include "Key.hpp"
#include "Verify.hpp"
#include "Transaction.hpp"
#include "Consensus/Contract.hpp"

using json = nlohmann::json;

class SPHINXChain {
public:
    class Chain {
    public:
        explicit Chain(const SPHINXParams::MainParams& mainParams); // Use the correct namespace for MainParams

        void addBlock(const SPHINXBlock::Block& block);

        std::string getBlockHash(uint32_t blockHeight) const;

        void transferFromSidechain(const SPHINXChain::Chain& sidechain, const std::string& blockHash);

        void handleBridgeTransaction(const std::string& bridge, const std::string& targetChain, const std::string& transaction);

        nlohmann::json toJson() const;

        void fromJson(const nlohmann::json& chainJson);

        bool save(const nlohmann::json& chainJson, const std::string& filename) const;

        static Chain load(const std::string& filename);

        SPHINXBlock::Block getGenesisBlock() const;

        SPHINXBlock::Block getBlockAt(size_t index) const;

        size_t getChainLength() const;

        void visualizeChain() const;

        void connectToSidechain(const Chain& sidechain);

        void transferFromSidechain(const std::string& sidechainAddress, const std::string& senderAddress, double amount);

        void createBlockchainBridge(const Chain& targetChain);

        void handleBridgeTransaction(const std::string& bridgeAddress, const std::string& recipientAddress, double amount);

        void performAtomicSwap(const Chain& targetChain, const std::string& senderAddress, const std::string& receiverAddress, double amount);

        void signTransaction(SPHINXTrx::Transaction& transaction);

        void broadcastTransaction(const SPHINXTrx::Transaction& transaction);

        void updateBalance(const std::string& address, double amount);

        double getBalance(const std::string& address) const;

        bool verifyAtomicSwap(const SPHINXTrx::Transaction& transaction, const Chain& targetChain) const;

        void handleTransfer(const SPHINXTrx::Transaction& transaction);

        std::string getBridgeAddress() const;

        std::string getBridgeSecret() const;

        void createShard(const std::string& shardName);

        void joinShard(const std::string& shardName, const Chain& shardChain);

        void transferToShard(const std::string& shardName, const std::string& senderAddress, const std::string& recipientAddress, double amount);

        void handleShardTransfer(const std::string& shardName, const SPHINXTrx::Transaction& transaction);

        void handleShardBridgeTransaction(const std::string& shardName, const std::string& bridgeAddress, const std::string& recipientAddress, double amount);

        void performShardAtomicSwap(const std::string& shardName, const Chain& targetShard, const std::string& senderAddress, const std::string& receiverAddress, double amount);

        void updateShardBalance(const std::string& shardName, const std::string& address, double amount);

        double getShardBalance(const std::string& shardName, const std::string& address) const;

        bool isChainValid() const;

    private:
        struct Shard {
            Chain chain;
            std::string bridgeAddress;
            std::string bridgeSecret;
            std::unordered_map<std::string, double> balances;
        };

        std::vector<Shard> shards_;
        std::vector<SPHINXBlock::Block> blocks_;
        SPHINXKey::vector SPHINXKeyPub;
        static constexpr uint32_t BLOCK_NOT_FOUND = std::numeric_limits<uint32_t>::max();
        std::unordered_map<std::string, uint32_t> shardIndices_;
        std::unordered_map<std::string, double> balances_;
        std::string bridgeAddress_;
        std::string bridgeSecret_;
        SPHINXChain::Chain targetChain_;

        SPHINXParams::MainParams mainParams_; // Use the correct namespace for MainParams
    };

     Chain::Chain(const SPHINXParams::MainParams& mainParams) : mainParams_(mainParams) {
        // Create the genesis block with the provided message
        SPHINXBlock::Block genesisBlock(mainParams_.genesisMessage);

        // Add the genesis block to the chain
        blocks_.push_back(genesisBlock);
    }

    void Chain::addBlock(const SPHINXBlock::Block& block) {
        // Add block to the blockchain
        // Calculate the hash of the block's data
        std::string blockHash = block.calculateBlockHash();

        // Sign the block's hash using the private key (Note: you need to define privateKey and transactionData somewhere)
        std::string signature = SPHINXVerify::sign_data(std::vector<uint8_t>(transactionData.begin(), transactionData.end()), privateKey);

        // Add the block and its signature to the chain
        blocks_.emplace_back(block, signature);
    }

    bool Chain::isChainValid() const {
        // Validate the integrity of the blockchain
        for (size_t i = 1; i < blocks_.size(); ++i) {
            const SPHINXBlock::Block& currentBlock = blocks_[i];
            const SPHINXBlock::Block& previousBlock = blocks_[i - 1];

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

    SPHINXBlock::Block Chain::getGenesisBlock() const {
        // Get the first block in the blockchain
        return blocks_.front();
    }

    SPHINXBlock::Block Chain::getBlockAt(size_t index) const {
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
            const SPHINXBlock::Block& block = blocks_[i];
            std::cout << "Block " << i << " - Hash: " << block.getBlockHash() << std::endl;
            // Print or display other block details as desired
        }
    }

    json Chain::toJson() const {
        json chainJson;
        chainJson["blocks"] = json::array();
        for (const SPHINXBlock::Block& block : blocks_) {
            chainJson["blocks"].push_back(block.toJson());
        }
        return chainJson;
    }

    void Chain::fromJson(const json& chainJson) {
        blocks_.clear();
        if (chainJson.contains("blocks") && chainJson["blocks"].is_array()) {
            const json& blocksJson = chainJson["blocks"];
            for (const json& blockJson : blocksJson) {
                SPHINXBlock::Block block;
                block.fromJson(blockJson);
                blocks_.push_back(block);
            }
        } else {
            throw std::invalid_argument("Invalid JSON structure or missing fields");
        }
    }

     // Sharding class for horizontal partitioning of the blockchain network
    class Sharding {
    public:
        static std::vector<Chain> shardBlockchain(const Chain& chain, size_t shardCount);
    };
} // namespace SPHINXChain

#endif // SPHINXCHAIN_HPP
