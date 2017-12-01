#include "HuffmanTreeNode.h"

HuffmanTreeNode::HuffmanTreeNode(std::string symbol, int freq, HuffmanTreeNode *left, HuffmanTreeNode *right)
  : _symbol{std::move(symbol)},
    _freq{freq},
    _left{left},
    _right{right} {

}

HuffmanTreeNode *HuffmanTreeNode::merge(HuffmanTreeNode *right) {
  return new HuffmanTreeNode{"", _freq + right->_freq, this, right};
}

int HuffmanTreeNode::freq() const {
  return _freq;
}

const std::string &HuffmanTreeNode::symbol() const {
  return this->_symbol;
}

std::string HuffmanTreeNode::symbol() {
  return this->_symbol;
}

HuffmanTreeNode *HuffmanTreeNode::left() const {
  return _left;
}

HuffmanTreeNode *HuffmanTreeNode::right() const {
  return _right;
}

bool HuffmanTreeNode::isLeaf() const {
  return _left == _right && _right == nullptr;
}

std::pair<HuffmanTreeNode *, HuffmanTreeNode *> HuffmanTreeNode::unpack() {
  auto childs = std::make_pair(_left, _right);
  _left = nullptr;
  _right = nullptr;
  return childs;
}
