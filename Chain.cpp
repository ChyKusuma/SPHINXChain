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
// This code defines a class called Chain that represents a blockchain. The Chain class has various member functions and data members that provide functionality for managing the blockchain and performing operations such as adding blocks, transferring funds, creating bridges, and handling transactions.

// Namespaces: The code starts with using directives for the json namespace from the nlohmann library, and forward declarations for the SPHINXBlock::Block class and SPHINXHash::SPHINX_256 and SPHINXTrx::SPHINXTrx functions.

// Class Declaration: The Chain class is declared and defined. It contains various member functions and data members that define the behavior and state of the blockchain.

// Data Members: The Chain class has several private data members:
    // shards_: A vector of Shard structs representing the shards of the chain.
    // blocks_: A vector of SPHINXBlock::Block objects representing the blocks of the chain.
    // publicKey_: A string representing the public key of the chain.
    // BLOCK_NOT_FOUND: A constant value representing an indicator for a block not found.
    // shardIndices_: An unordered map that stores the indices of shards by shard name for quick access.
    // balances_: An unordered map that stores the balances of addresses in the chain.
    // bridgeAddress_: A string representing the bridge address of the chain.
    // bridgeSecret_: A string representing the bridge secret of the chain.
    // targetChain_: An instance of the Chain class representing the target chain.

// Constructor: The Chain class has a default constructor that initializes the blockchain with a genesis block.

// Member Functions: The Chain class provides various member functions to perform operations on the blockchain. Here are some of the key member functions:

    // addBlock: Adds a block to the chain.
    // getBlockHash: Retrieves the hash of a block at a specific height in the chain.
    // transferFromSidechain: Transfers blocks from a sidechain to the main chain.
    // handleBridgeTransaction: Handles a transaction from a bridge to the target chain.
    // toJson and fromJson: Convert the chain to and from JSON format.
    // save and load: Save and load the chain data to and from a file.
    // getGenesisBlock: Retrieves the genesis block of the chain.
    // getBlockAt: Retrieves a block at a specific index in the chain.
    // getChainLength: Retrieves the length of the chain.
    // visualizeChain: Prints a visualization of the chain.
    // connectToSidechain: Connects to a sidechain.
    // transferFromSidechain: Transfers funds from a sidechain to the main chain.
    // createBlockchainBridge: Creates a bridge between the current chain and a target chain.
    // handleBridgeTransaction: Handles a bridge transaction.
    // performAtomicSwap: Performs an atomic swap with another chain.
    // signTransaction and broadcastTransaction: Sign and broadcast a transaction to the network.
    // updateBalance and getBalance: Update and retrieve the balance of an address.
    // verifyAtomicSwap: Verifies an atomic swap transaction.
    // handleTransfer: Handles a transfer transaction.
    // getBridgeAddress and getBridgeSecret: Retrieves the bridge address and secret of the chain.

// Sharding chain functionality: The chain also supports sharding functionality with member functions for creating shards, joining shards, transferring funds to shards, handling shard transfers, performing shard atomic swaps, updating shard balances, and getting shard balances.

// Overall, the Chain class provides a set of functions and data members to manage and interact with a blockchain. It supports basic blockchain operations, transaction handling, bridge creation and transaction handling, atomic swaps, and sharding functionality.
/////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <unordered_map>
#include <limits>
#include <chrono>
#include <thread>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "Chain.hpp"
#include "json.hpp"
#include "Block.hpp"
#include "Verify.hpp"
#include "Sign.hpp"
#include "Key.hpp"
#include "Verify.hpp"
#include "Trx.hpp"


using json = nlohmann::json;

// Forward declarations
namespace SPHINXBlock {
    std::string SPHINXBlock (const std::string& message);
}

namespace SPHINXHash {
    std::string SPHINX_256(const std::string& message);
}

namespace SPHINXTrx {
    std::string SPHINXTrx(const std::string& message);
}

class SPHINXContract {
public:
    // Executes the given chain
    void executeChain(SPHINX_Chain::Chain& chain);

    // Handles a bridge transaction on the chain
    void handleBridgeTransaction(SPHINX_Chain::Chain& chain, const std::string& bridge, const std::string& targetChain, const std::string& transaction);

    // Handles a transfer transaction on the chain
    void handleTransfer(SPHINX_Chain::Chain& chain, const SPHINXTrx::Transaction& transaction);

    // Handles a shard transfer transaction on the chain
    void handleShardTransfer(SPHINX_Chain::Chain& chain, const std::string& shardName, const SPHINXTrx::Transaction& transaction);

    // Handles a shard bridge transaction on the chain
    void handleShardBridgeTransaction(SPHINX_Chain::Chain& chain, const std::string& shardName, const std::string& bridgeAddress, const std::string& recipientAddress, double amount);

    // Handles an atomic swap between chains
    void handleAtomicSwap(SPHINX_Chain::Chain& chain, const SPHINX_Chain::Chain& targetChain, const std::string& senderAddress, const std::string& receiverAddress, double amount);

private:
    std::unordered_map<std::string, double> balances_;  // Balances of addresses on the chain
    std::string bridgeAddress_;  // Address of the bridge
    std::string bridgeSecret_;  // Secret key for the bridge
    SPHINX_Chain::Chain targetChain_;  // Target chain for atomic swaps
};

class SPHINX_Chain {
public:
    class Chain {
    public:
        Chain();

        // Adds a block to the chain
        void addBlock(const SPHINXBlock::Block& block);

        // Retrieves the hash of a block at the given height
        std::string getBlockHash(uint32_t blockHeight) const;

        // Transfers funds from a sidechain to the chain
        void transferFromSidechain(const SPHINX_Chain::Chain& sidechain, const std::string& blockHash);

        // Handles a bridge transaction on the chain
        void handleBridgeTransaction(const std::string& bridge, const std::string& targetChain, const std::string& transaction);

        // Converts the chain to JSON format
        nlohmann::json toJson() const;

        // Populates the chain from a JSON object
        void fromJson(const nlohmann::json& chainJson);

        // Saves the chain to a file
        bool save(const nlohmann::json& chainJson, const std::string& filename) const;

        // Loads a chain from a file
        static Chain load(const std::string& filename);

        // Retrieves the genesis block of the chain
        SPHINXBlock::Block getGenesisBlock() const;

        // Retrieves the block at the given index
        SPHINXBlock::Block getBlockAt(size_t index) const;

        // Retrieves the length of the chain
        size_t getChainLength() const;

        // Visualizes the chain
        void visualizeChain() const;

        // Connects the chain to a sidechain
        void connectToSidechain(const Chain& sidechain);

        // Transfers funds from a sidechain to the chain
        void transferFromSidechain(const std::string& sidechainAddress, const std::string& senderAddress, double amount);

        // Creates a bridge between the chain and the target chain
        void createBlockchainBridge(const Chain& targetChain);

        // Handles a bridge transaction on the chain
        void handleBridgeTransaction(const std::string& bridgeAddress, const std::string& recipientAddress, double amount);

        // Performs an atomic swap with the target chain
        void performAtomicSwap(const Chain& targetChain, const std::string& senderAddress, const std::string& receiverAddress, double amount);

        // Signs a transaction
        void signTransaction(SPHINXTrx::Transaction& transaction);

        // Broadcasts a transaction
        void broadcastTransaction(const SPHINXTrx::Transaction& transaction);

        // Updates the balance of an address on the chain
        void updateBalance(const std::string& address, double amount);

        // Retrieves the balance of an address on the chain
        double getBalance(const std::string& address) const;

        // Verifies the validity of an atomic swap transaction with the target chain
        bool verifyAtomicSwap(const SPHINXTrx::Transaction& transaction, const Chain& targetChain) const;

        // Handles a transfer transaction on the chain
        void handleTransfer(const SPHINXTrx::Transaction& transaction);

        // Retrieves the address of the bridge
        std::string getBridgeAddress() const;

        // Retrieves the secret key of the bridge
        std::string getBridgeSecret() const;

        // Creates a shard on the chain
        void createShard(const std::string& shardName);

        // Joins a shard to the chain
        void joinShard(const std::string& shardName, const Chain& shardChain);

        // Transfers funds to a shard on the chain
        void transferToShard(const std::string& shardName, const std::string& senderAddress, const std::string& recipientAddress, double amount);

        // Handles a shard transfer transaction on the chain
        void handleShardTransfer(const std::string& shardName, const SPHINXTrx::Transaction& transaction);

        // Handles a shard bridge transaction on the chain
        void handleShardBridgeTransaction(const std::string& shardName, const std::string& bridgeAddress, const std::string& recipientAddress, double amount);

        // Performs an atomic swap with a shard on the chain
        void performShardAtomicSwap(const std::string& shardName, const Chain& targetShard, const std::string& senderAddress, const std::string& receiverAddress, double amount);

        // Updates the balance of an address on a shard
        void updateShardBalance(const std::string& shardName, const std::string& address, double amount);

        // Retrieves the balance of an address on a shard
        double getShardBalance(const std::string& shardName, const std::string& address) const;

        friend class SPHINXContract;

    private:
        // Represents a shard in the chain
        struct Shard {
            Chain chain;
            std::string bridgeAddress;
            std::string bridgeSecret;
            std::unordered_map<std::string, double> balances;
        };

        std::vector<Shard> shards_;  // Shards in the chain
        std::vector<SPHINXBlock::Block> blocks_;  // Blocks in the chain
        std::string publicKey_;  // Public key of the chain
        static constexpr uint32_t BLOCK_NOT_FOUND = std::numeric_limits<uint32_t>::max();  // Constant for block not found
        std::unordered_map<std::string, uint32_t> shardIndices_;  // Indices of shards in the chain

        std::unordered_map<std::string, double> balances_;  // Balances of addresses on the chain
        std::string bridgeAddress_;  // Address of the bridge
        std::string bridgeSecret_;  // Secret key for the bridge
        SPHINX_Chain::Chain targetChain_;  // Target chain for atomic swaps
    };


    // Genesis block
    Chain::Chain() {
        std::string genesisMessage = "Welcome to Post-Quantum era, The Beginning of a Secured-Trustless Network will start from here - SPHINX Network";
        SPHINXBlock::Block genesisBlock(SPHINXHash::SPHINX_256(genesisMessage));
        addBlock(genesisBlock);  
    }

    void Chain::addBlock(const SPHINXBlock::Block& block) {
        if (blocks_.empty()) {  // If the chain is empty
            blocks_.push_back(block);  // Add the block to the chain
        } else {
            if (block.verifyBlock(publicKey_)) {  // Verify the block using the public key
                blocks_.push_back(block);  // Add the block to the chain
            } else {
                throw std::runtime_error("Invalid block! Block verification failed.");  // Throw an error if the block verification fails
            }
        }
    }

    bool isChainValid() const {
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

    std::string Chain::getBlockHash(uint32_t blockHeight) const {
        if (blockHeight >= blocks_.size()) {  // If the block height is out of range
            throw std::out_of_range("Block height out of range.");  // Throw an out-of-range error
        }
        return blocks_[blockHeight].getBlockHash();  // Get the hash of the block at the given height
    }

    void Chain::transferFromSidechain(const SPHINX_Chain::Chain& sidechain, const std::string& blockHash) {
        uint32_t blockHeight = BLOCK_NOT_FOUND;  // Initialize the block height variable
        for (uint32_t i = 0; i < sidechain.getChainLength(); ++i) {  // Iterate over the blocks in the sidechain
            if (sidechain.getBlockHash(i) == blockHash) {  // Check if the block hash matches the given block hash
                blockHeight = i;  // Store the block height
                break;
            }
        }

        if (blockHeight == BLOCK_NOT_FOUND) {  // If the block is not found in the main chain
            throw std::runtime_error("Block not found in the main chain.");  // Throw an error
        }

        const SPHINXBlock::Block& block = sidechain.getBlockAt(blockHeight);  // Get the block at the specified height from the sidechain
        if (block.verifyBlock(publicKey_)) {  // Verify the block using the public key
            blocks_.push_back(block);  // Add the block to the chain
        } else {
            throw std::runtime_error("Invalid block! Block verification failed.");  // Throw an error if the block verification fails
        }
    }

    void Chain::handleBridgeTransaction(const std::string& bridge, const std::string& targetChain, const std::string& transaction) {
        if (bridge == "SPHINX") {  // Check if the bridge is "SPHINX"
            bool isValid = SPHINXVerify::validateTransaction(transaction);  // Validate the transaction
            if (!isValid) {  // If the transaction is not valid
                throw std::runtime_error("Invalid transaction! Transaction validation failed.");  // Throw an error
            }
            targetChain_.addTransaction(transaction);  // Add the transaction to the target chain
        } else {
            throw std::runtime_error("Invalid bridge!");  // If the bridge is invalid, throw an error
        }
    }

    nlohmann::json Chain::toJson() const {
        nlohmann::json chainJson;
        // Serialize the blocks
        nlohmann::json blocksJson = nlohmann::json::array();
        for (const SPHINXBlock::Block& block : blocks_) {
            blocksJson.push_back(block.toJson());
        }
        chainJson["blocks"] = blocksJson;

        // Serialize the public key
        chainJson["publicKey"] = publicKey_;

        return chainJson;
    }

    void Chain::fromJson(const nlohmann::json& chainJson) {
        blocks_.clear();

        // Deserialize the blocks
        const nlohmann::json& blocksJson = chainJson["blocks"];
        for (const auto& blockJson : blocksJson) {
            SPHINXBlock::Block block("");
            block.fromJson(blockJson);
            blocks_.push_back(block);
        }

        // Deserialize the public key
        publicKey_ = chainJson["publicKey"].get<std::string>();
    }

    bool Chain::save(const nlohmann::json& chainJson, const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << chainJson.dump(4);  // Write the formatted JSON data to the file
            outputFile.close();
            return true;
        }
        return false;
    }

    Chain Chain::load(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (inputFile.is_open()) {
            json chainJson;
            inputFile >> chainJson;  // Read the JSON data from the file
            inputFile.close();
            Chain loadedChain;
            loadedChain.fromJson(chainJson);  // Deserialize the JSON data into a Chain object
            return loadedChain;
        }
        throw std::runtime_error("Failed to load chain from file: " + filename);
    }

    SPHINXBlock::Block Chain::getGenesisBlock() const {
        return blocks_.front();  // Return the first block in the chain
    }

    SPHINXBlock::Block Chain::getBlockAt(size_t index) const {
        if (index < blocks_.size()) {
            return blocks_[index];  // Return the block at the specified index
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    size_t Chain::getChainLength() const {
        return blocks_.size();  // Return the number of blocks in the chain
    }

    void Chain::visualizeChain() const {
        for (size_t i = 0; i < blocks_.size(); ++i) {
            const SPHINXBlock::Block& block = blocks_[i];
            std::cout << "Block " << i << " - Hash: " << block.getBlockHash() << std::endl;  // Print the index and hash of each block
        }
    }

    void Chain::connectToSidechain(const Chain& sidechain) {
        SidechainConnection connection(sidechain.getBridgeAddress(), sidechain.getBridgeSecret());  // Create a connection to the sidechain using its bridge address and secret
        connection.sync();  // Synchronize the connection
    }

    void Chain::transferFromSidechain(const std::string& sidechainAddress, const std::string& senderAddress, double amount) {
        double senderBalance = getBalance(senderAddress);  // Get the balance of the sender
        if (amount > senderBalance) {
            throw std::runtime_error("Sender does not have enough funds");  // Throw an error if the sender doesn't have enough funds
        }

        if (!TwoFactorAuthenticator::verifyCode(senderUsername, sender2FACode)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        SPHINXKey::HybridKeypair keyPair = SPHINXKey::generate_and_perform_key_exchange();  // Generate and perform a key exchange
        std::string publicKey = SPHINXKey::calculatePublicKey(keyPair.merged_key.kyber_private_key.data());  // Calculate the public key
        SPHINXTrx::Transaction transferTransaction = createTransaction(sidechainAddress, senderAddress, amount);  // Create a transaction
        signTransaction(transferTransaction);  // Sign the transaction
        broadcastTransaction(transferTransaction);  // Broadcast the transaction
        handleTransfer(transferTransaction);  // Handle the transfer
    }

    void Chain::createBlockchainBridge(const Chain& targetChain) {
        std::string bridgeAddress = generateBridgeAddress();  // Generate a bridge address for the current chain
        std::string targetBridgeAddress = targetChain.generateBridgeAddress();  // Generate a bridge address for the target chain
        std::shared_ptr<CloudflareSecureBridgeConnection> connection = std::make_shared<CloudflareSecureBridgeConnection>(bridgeAddress, targetBridgeAddress);  // Create a connection using the bridge addresses
        connection->createBridge();  // Create a bridge using the connection
    }

    void Chain::handleBridgeTransaction(const std::string& bridgeAddress, const std::string& recipientAddress, double amount) {
        if (!bridge.verifyTransaction(bridgeAddress, amount)) {
            throw std::runtime_error("Invalid bridge transaction");  // Throw an error if the bridge transaction is invalid
        }

        if (!TwoFactorAuthenticator::verifyCode(senderUsername, sender2FACode)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        SPHINXKey::HybridKeypair keyPair = SPHINXKey::generate_and_perform_key_exchange();  // Generate and perform a key exchange
        std::string publicKey = SPHINXKey::calculatePublicKey(keyPair.merged_key.kyber_private_key.data());  // Calculate the public key
        std::string transactionData = bridge.getTransactionData(bridgeAddress);  // Get the transaction data from the bridge
        std::string signature = SPHINXSign::sign(transactionData, keyPair.merged_key.kyber_private_key.data());  // Sign the transaction data

        if (!SPHINXVerify::verifySignature(transactionData, signature, publicKey)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if the signature verification fails
        }

        std::string transactionHash = SPHINXHash::SPHINX_256(transactionData);  // Calculate the transaction hash
        targetChain.transfer(recipientAddress, amount);  // Transfer funds to the recipient address in the target chain
        updateBalance(recipientAddress, amount);  // Update the balance of the recipient address
        updateBalance(senderAddress, -amount);  // Update the balance of the sender address
    }

    void Chain::performAtomicSwap(const Chain& targetChain, const std::string& senderAddress, const std::string& receiverAddress, double amount) {
        double senderBalance = getBalance(senderAddress);  // Get the balance of the sender address
        double receiverBalance = targetChain.getBalance(receiverAddress);  // Get the balance of the receiver address in the target chain
        if (senderBalance < amount) {
            throw std::runtime_error("Sender does not have enough funds");  // Throw an error if the sender doesn't have enough funds
        }

        if (!TwoFactorAuthenticator::verifyCode(senderUsername, sender2FACode)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        SPHINXTrx::Transaction senderTransaction = createTransaction(senderAddress, targetChain.getBridgeAddress(), amount);  // Create a transaction from the sender address to the target chain bridge address
        SPHINXTrx::Transaction receiverTransaction = targetChain.createTransaction(receiverAddress, senderAddress, amount);  // Create a transaction from the receiver address in the target chain to the sender address

        signTransaction(senderTransaction);  // Sign the sender transaction
        signTransaction(receiverTransaction);  // Sign the receiver transaction
        broadcastTransaction(senderTransaction);  // Broadcast the sender transaction
        targetChain.broadcastTransaction(receiverTransaction);  // Broadcast the receiver transaction

        while (true) {
            if (senderTransaction.isConfirmed() && receiverTransaction.isConfirmed()) {
                break;  // Exit the loop if both transactions are confirmed
            }
            std::this_thread::sleep_for(std::chrono::seconds(10));  // Sleep for 10 seconds before checking the confirmation status again
        }

        if (!verifyAtomicSwap(senderTransaction, targetChain) || !targetChain.verifyAtomicSwap(receiverTransaction, *this)) {
            throw std::runtime_error("Atomic swap verification failed");  // Throw an error if the atomic swap verification fails
        }

        updateBalance(senderAddress, -amount);  // Update the balance of the sender address
        targetChain.updateBalance(receiverAddress, amount);  // Update the balance of the receiver address in the target chain
    }

    void Chain::signTransaction(SPHINXTrx::Transaction& transaction) {
        std::string transactionData = bridge.getTransactionData(bridgeAddress_);  // Get the transaction data from the bridge
        std::string privateKey = SPHINXSign::getPrivateKey();  // Get the private key
        std::string signature = SPHINXSign::sign(transactionData, privateKey);  // Sign the transaction data using the private key
        transaction.setSignature(signature);  // Set the transaction signature
    }

    void Chain::broadcastTransaction(const SPHINXTrx::Transaction& transaction) {
        std::string transactionJson = transaction.toJson().dump();  // Convert the transaction to JSON
        bridge.broadcastTransaction(bridgeAddress_, transactionJson);  // Broadcast the transaction via the bridge
    }

    void Chain::updateBalance(const std::string& address, double amount) {
        balances_[address] += amount;  // Update the balance of the given address by adding the specified amount
    }

    double Chain::getBalance(const std::string& address) const {
        if (balances_.count(address) > 0) {
            return balances_.at(address);  // Return the balance of the given address if it exists
        }
        return 0.0;  // Return 0 if the balance of the given address is not found
    }

    bool Chain::verifyAtomicSwap(const SPHINXTrx::Transaction& transaction, const Chain& targetChain) const {
        std::string transactionData = bridge.getTransactionData(bridgeAddress_);
        std::string signature = transaction.getSignature();
        std::string senderPublicKey = transaction.getSenderPublicKey();
        // Verify the transaction signature and the bridge transaction in the target chain
        return SPHINXVerify::verifySignature(transactionData, signature, senderPublicKey) && targetChain.verifyBridgeTransaction(transaction);
    }

    void Chain::handleTransfer(const SPHINXTrx::Transaction& transaction) {
        std::string recipientAddress = transaction.getRecipientAddress();
        double amount = transaction.getAmount();
        updateBalance(recipientAddress, amount);  // Update the balance of the recipient address
    }

    std::string Chain::getBridgeAddress() const {
        return bridgeAddress_;
    }

    std::string Chain::getBridgeSecret() const {
        return bridgeSecret_;
    }

    // Sharding chain functionality
    void Chain::createShard(const std::string& shardName) {
        Shard shard;
        shard.bridgeAddress = shardName;
        shard.chain = Chain();
        shards_.push_back(shard);  // Add a new shard to the shard vector
        shardIndices_[shardName] = shards_.size() - 1;  // Store the shard index by shard name for quick access
    }

    void Chain::joinShard(const std::string& shardName, const Chain& shardChain) {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        shards_[it->second].chain = shardChain;  // Join the shard by assigning the shard chain to the corresponding shard
    }

    void Chain::transferToShard(const std::string& shardName, const std::string& senderAddress, const std::string& recipientAddress, double amount) {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        Shard& shard = shards_[it->second];  // Get the reference to the shard
        double senderBalance = getBalance(senderAddress);
        if (amount > senderBalance) {
            throw std::runtime_error("Sender does not have enough funds");  // Throw an error if the sender doesn't have enough funds
        }

        if (!TwoFactorAuthenticator::verifyCode(senderUsername, sender2FACode)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        SPHINXKey::HybridKeypair keyPair = SPHINXKey::generate_and_perform_key_exchange();  // Generate and perform a key exchange
        std::string publicKey = SPHINXKey::calculatePublicKey(keyPair.merged_key.kyber_private_key.data());  // Calculate the public key
        SPHINXTrx::Transaction transferTransaction = createTransaction(shard.bridgeAddress, senderAddress, amount);  // Create a transaction to the shard bridge address
        signTransaction(transferTransaction);  // Sign the transaction
        broadcastTransaction(transferTransaction);  // Broadcast the transaction
        shard.chain.handleShardTransfer(shardName, transferTransaction);  // Handle the shard transfer in the shard chain
        updateBalance(senderAddress, -amount);  // Update the balance of the sender address
    }

    void Chain::handleShardTransfer(const std::string& shardName, const SPHINXTrx::Transaction& transaction) {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        Shard& shard = shards_[it->second];  // Get the reference to the shard
        shard.chain.handleTransfer(transaction);  // Handle the transfer in the shard chain
    }

    void Chain::handleShardBridgeTransaction(const std::string& shardName, const std::string& bridgeAddress, const std::string& recipientAddress, double amount) {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        Shard& shard = shards_[it->second];  // Get the reference to the shard
        if (!shard.bridge.verifyTransaction(bridgeAddress, amount)) {
            throw std::runtime_error("Invalid bridge transaction");  // Throw an error if the bridge transaction is invalid
        }

        if (!TwoFactorAuthenticator::verifyCode(senderUsername, sender2FACode)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        SPHINXKey::HybridKeypair keyPair = SPHINXKey::generate_and_perform_key_exchange();  // Generate and perform a key exchange
        std::string publicKey = SPHINXKey::calculatePublicKey(keyPair.merged_key.kyber_private_key.data());  // Calculate the public key
        std::string transactionData = shard.bridge.getTransactionData(bridgeAddress);  // Get the transaction data from the shard bridge
        std::string signature = SPHINXSign::sign(transactionData, keyPair.merged_key.kyber_private_key.data());  // Sign the transaction data

        if (!SPHINXVerify::verifySignature(transactionData, signature, publicKey)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        std::string transactionHash = SPHINXHash::SPHINX_256(transactionData);
        shard.chain.updateBalance(recipientAddress, amount);  // Update the balance of the recipient address in the shard chain
        shard.chain.updateBalance(senderAddress, -amount);  // Update the balance of the sender address in the shard chain
    }

    void Chain::performShardAtomicSwap(const std::string& shardName, const Chain& targetShard, const std::string& senderAddress, const std::string& receiverAddress, double amount) {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        Shard& shard = shards_[it->second];  // Get the reference to the shard
        double senderBalance = getBalance(senderAddress);
        double receiverBalance = targetShard.getBalance(receiverAddress);
        if (senderBalance < amount) {
            throw std::runtime_error("Sender does not have enough funds");  // Throw an error if the sender does not have enough funds
        }

        if (!TwoFactorAuthenticator::verifyCode(senderUsername, sender2FACode)) {
            throw std::runtime_error("Authentication failed");  // Throw an error if authentication fails
        }

        SPHINXTrx::Transaction senderTransaction = createTransaction(senderAddress, shard.bridgeAddress, amount);  // Create a transaction from the sender to the shard bridge
        SPHINXTrx::Transaction receiverTransaction = targetShard.createTransaction(receiverAddress, senderAddress, amount);  // Create a transaction from the shard bridge to the receiver

        signTransaction(senderTransaction);  // Sign the sender transaction
        signTransaction(receiverTransaction);  // Sign the receiver transaction
        broadcastTransaction(senderTransaction);  // Broadcast the sender transaction
        targetShard.broadcastTransaction(receiverTransaction);  // Broadcast the receiver transaction

        while (true) {
            if (senderTransaction.isConfirmed() && receiverTransaction.isConfirmed()) {
                break;  // Wait until both transactions are confirmed
            }
            std::this_thread::sleep_for(std::chrono::seconds(10));  // Sleep for 10 seconds before checking confirmation status again
        }

        if (!verifyAtomicSwap(senderTransaction, shard.chain) || !targetShard.verifyAtomicSwap(receiverTransaction, shard.chain)) {
            throw std::runtime_error("Atomic swap verification failed");  // Throw an error if atomic swap verification fails
        }

        updateBalance(senderAddress, -amount);  // Update the balance of the sender address
        targetShard.updateBalance(receiverAddress, amount);  // Update the balance of the receiver address in the target shard
    }

    void Chain::updateShardBalance(const std::string& shardName, const std::string& address, double amount) {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        Shard& shard = shards_[it->second];  // Get the reference to the shard
        shard.balances[address] += amount;  // Update the balance of the given address in the shard
    }

    double Chain::getShardBalance(const std::string& shardName, const std::string& address) const {
        auto it = shardIndices_.find(shardName);
        if (it == shardIndices_.end()) {
            throw std::runtime_error("Shard does not exist: " + shardName);  // Throw an error if the shard does not exist
        }
        const Shard& shard = shards_[it->second];  // Get the reference to the shard
        if (shard.balances.count(address) > 0) {
            return shard.balances.at(address);  // Return the balance of the given address in the shard if it exists
        }
        return 0.0;  // Return 0.0 if the address balance is not found in the shard
    }
} // namespace SPHINX_Chain
