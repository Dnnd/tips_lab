//
// Created by danm on 06.11.17.
//

#ifndef LAB_TIPS_HUFFMANTREE_H
#define LAB_TIPS_HUFFMANTREE_H

#include <map>
#include <vector>
#include <unordered_map>
#include <queue>
#include "HuffmanTreeNode.h"

class HuffmanTree {
public:
  using NodesHeap = std::priority_queue<HuffmanTreeNode *, std::deque<HuffmanTreeNode *>, HuffmanTreeNodeComparator>;
  using CodeTable = std::unordered_map<std::string, std::vector<bool>>;
  using FreqTable = std::unordered_map<std::string, int>;

  HuffmanTree();

  explicit HuffmanTree(FreqTable freq_table);

  HuffmanTree(HuffmanTree &&other) noexcept;

  HuffmanTree& operator=(HuffmanTree &&other) noexcept;
  static HuffmanTreeNode *buildHuffmanTree(FreqTable &&freq_table);

  static CodeTable buildCodeTable(const HuffmanTreeNode *root);

  const HuffmanTreeNode *root() const {
    return _root;
  }

  std::string getSymbolByCode(const std::vector<bool> &code);

  const std::vector<bool> &getCodeBySymbol(const std::string &code);

   ~HuffmanTree();

private:
  void cleanup() noexcept ;
  HuffmanTreeNode *_root;
  CodeTable _code_table;
};


#endif //LAB_TIPS_HUFFMANTREE_H
