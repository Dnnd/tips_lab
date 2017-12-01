#include <queue>
#include <stack>
#include <iostream>
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree()
  : _root{nullptr},
    _code_table{} {

}


HuffmanTree::HuffmanTree(std::unordered_map<std::string, int> freq_table)
  : _root{buildHuffmanTree(std::move(freq_table))},
    _code_table{buildCodeTable(_root)} {

}

HuffmanTree::CodeTable HuffmanTree::buildCodeTable(const HuffmanTreeNode *root) {
  std::stack<std::pair<const HuffmanTreeNode *, bool>> dfs;
  CodeTable code_table;
  dfs.push({root, true});
  std::vector<bool> path;
  while (!dfs.empty()) {
    auto[top, isLeft] = dfs.top();
    dfs.pop();
    if (top->isLeaf() && isLeft) {
      code_table[top->symbol()] = path;
      path.back() = false;
    } else if (top->isLeaf() && !isLeft) {
      code_table[top->symbol()] = path;
      while (!path.empty() && path.back() != true) {
        path.pop_back();
      }
      if (path.empty()) {
        break;
      } else {
        path.back() = false;
      }
    } else {
      dfs.push({top->right(), false});
      dfs.push({top->left(), true});
      path.push_back(true);
    }
  }
  return std::move(code_table);
}

HuffmanTreeNode *HuffmanTree::buildHuffmanTree(HuffmanTree::FreqTable &&freq_table) {
  NodesHeap nodes{HuffmanTreeNodeComparator()};
  for (auto[key, freq]: freq_table) {
     nodes.push(new HuffmanTreeNode(key, freq));
  }
  while (nodes.size() > 1) {
    auto left = nodes.top();
    nodes.pop();
    auto right = nodes.top();
    nodes.pop();
    auto merged = left->merge(right);
    nodes.push(merged);
  }
  HuffmanTreeNode* root = nodes.top();
  nodes.pop();

  return root;
}

std::string HuffmanTree::getSymbolByCode(const std::vector<bool> &code) {
  const auto *iter = this->_root;
  for (auto bit: code) {
    if (iter->isLeaf()) {
      return "";
    }
    if (bit) {
      iter = iter->left();
    } else {
      iter = iter->right();
    }
  }
  return iter->symbol();
}

const std::vector<bool> &HuffmanTree::getCodeBySymbol(const std::string &symbol) {
  return _code_table[symbol];
}

HuffmanTree::~HuffmanTree() {
  cleanup();
}

HuffmanTree::HuffmanTree(HuffmanTree &&other) noexcept {
  this->_root = other._root;
  this->_code_table = std::move(other._code_table);
  other._root = nullptr;
}

HuffmanTree &HuffmanTree::operator=(HuffmanTree &&other) noexcept {
  cleanup();
  this->_root = other._root;
  this->_code_table = std::move(other._code_table);
  other._root = nullptr;
}

void HuffmanTree::cleanup() noexcept {
  if (_root == nullptr) {
    return;
  }
  std::stack<HuffmanTreeNode *> dfs;
  dfs.push(_root);
  while (!dfs.empty()) {
    auto top = dfs.top();
    if (!top->isLeaf()) {
      auto[left, right] = top->unpack();
      dfs.push(left);
      dfs.push(right);
    } else {
      delete top;
      dfs.pop();
    }
  }
}

