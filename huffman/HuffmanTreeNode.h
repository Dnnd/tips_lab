
#ifndef LAB_TIPS_HUFFMANTREENODE_H
#define LAB_TIPS_HUFFMANTREENODE_H


#include <string>

class HuffmanTreeNode {
public:
  HuffmanTreeNode(std::string _symbol, int freq, HuffmanTreeNode *left = nullptr, HuffmanTreeNode *right = nullptr);

  HuffmanTreeNode *merge(HuffmanTreeNode *left);

  int freq() const;

  const std::string &symbol() const;

  std::string symbol();

  HuffmanTreeNode *left() const;

  HuffmanTreeNode *right() const;;

  bool isLeaf() const;

  std::pair<HuffmanTreeNode *, HuffmanTreeNode *> unpack();

private:
  std::string _symbol;
  int _freq;
  HuffmanTreeNode *_left;
  HuffmanTreeNode *_right;
};

struct HuffmanTreeNodeComparator {
  bool operator()(const HuffmanTreeNode *right, const HuffmanTreeNode *left) {
    return right->freq() > left->freq();
  }
};

#endif //LAB_TIPS_HUFFMANTREENODE_H
