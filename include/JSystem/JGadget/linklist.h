#ifndef JGADGET_LINK_H
#define JGADGET_LINK_H

#include "types.h"

#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JGadget/define.h"

namespace JGadget {

namespace {

template <typename T>
class TPRIsEqual_pointer_ {
public:
  TPRIsEqual_pointer_<T>(const T* p) { this->p_ = p; }

  bool operator()(const T& rSrc) const {
    return this->p_ == &rSrc;
  }

private:
  const T* p_;
};

}

class TLinkListNode {
public:
  TLinkListNode() {
    this->pNext_ = nullptr;
    this->pPrev_ = nullptr;
  }

  ~TLinkListNode();

  TLinkListNode* getNext() const {
    return this->pNext_;
  }

  TLinkListNode* getPrev() const {
    return this->pPrev_;
  }

  void clear_();

  TLinkListNode* pNext_;
  TLinkListNode* pPrev_;
};

class TNodeLinkList {
public:
  TNodeLinkList();
  ~TNodeLinkList();

  class iterator {
  public:
    iterator() { this->p_ = nullptr; }
    iterator(TLinkListNode* node) { this->p_ = node; }

    iterator& operator++() {
      this->p_ = this->p_->getNext();
      return *this;
    }

    iterator& operator--() {
      this->p_ = this->p_->getPrev();
      return *this;
    }

    TLinkListNode& operator*() const {
      JUT_ASSERT(p_!=0);
      return *this->p_;
    }

    TLinkListNode* operator->() const { return this->p_; }
    
    TLinkListNode* p_;
  };

  class const_iterator {
  public:
    const_iterator(const TLinkListNode* node) { this->p_ = node; }
    const_iterator(iterator it) { this->p_ = it.p_; }

    const const_iterator& operator++() {
      this->p_ = this->p_->getNext();
      return *this;
    }

    const const_iterator& operator--() {
      this->p_ = this->p_->getPrev();
      return *this;
    }

    const TLinkListNode* operator->() const { return this->p_; }
    
    const TLinkListNode* p_;
  };

  bool Confirm() const;
  bool Confirm_iterator(const_iterator it) const;
  iterator Erase(TLinkListNode* node);
  iterator Find(const TLinkListNode* node);
  iterator Insert(iterator it, TLinkListNode* node);
  void Remove(TLinkListNode* node);
  template <typename Predicate> void Remove_if(Predicate predicate, TNodeLinkList& other);

  s32 size() const { return this->size_; }
  bool empty() const { return this->size() == 0; }
  void clear() { this->erase(this->begin(), this->end()); }
  iterator erase(iterator itStart, iterator itEnd);
  iterator erase(iterator it);
  template <typename Predicate> void remove_if(Predicate predicate) {
    TNodeLinkList list;

    this->Remove_if(predicate, list);
  }
  void splice(iterator it, TNodeLinkList& rSrc, iterator itBegin, iterator itEnd);
  void splice(iterator it, TNodeLinkList& rSrc);
  void splice(iterator it, TNodeLinkList& rSrc, iterator otherIt);
  iterator pop_back() { return this->erase(--this->end()); }
  iterator pop_font() { return this->erase(++this->begin()); }
  
  iterator begin() { return this->oNode_.getNext(); }
  const_iterator begin() const { return this->oNode_.getNext(); }
  
  iterator end() { return &this->oNode_; }
  const_iterator end() const { return &this->oNode_; }

private:
  void Initialize_();
  bool Iterator_isEnd_(const_iterator it) const { return &this->oNode_ == it.p_; }

  s32 size_;
  TLinkListNode oNode_;
};

bool operator==(TNodeLinkList::iterator lhs, TNodeLinkList::iterator rhs) { return lhs.p_ == rhs.p_; }
bool operator!=(TNodeLinkList::iterator lhs, TNodeLinkList::iterator rhs) { return !(lhs == rhs); }

bool operator==(TNodeLinkList::const_iterator lhs, TNodeLinkList::const_iterator rhs) { return lhs.p_ == rhs.p_; }
bool operator!=(TNodeLinkList::const_iterator lhs, TNodeLinkList::const_iterator rhs) { return !(lhs == rhs); }

template <typename T, int O>
class TLinkList : public TNodeLinkList {
  class iterator {
  public:
    iterator iterator(TNodeLinkList::iterator it) : mIt(it) {  }

    bool operator==(iterator other) { return (mIt == other.mIt);  }
    bool operator!=(iterator other) { return !(*this == other); }
    iterator& operator++() {
      ++mIt;
      return *this;
    }
    iterator& operator--() {
      --mIt;
      return *this;
    }

    T* operator->() const { return TLinkList::Element_toValue(TNodeLinkList::iterator::operator->(mIt)); }
    T& operator*() const {
      T* p = TLinkList::iterator::operator->();
      #line 541
      JUT_ASSERT(p!=0);
      return *p;
    }

  private:
    TNodeLinkList::iterator mIt;
  };

  class const_iterator {
  public:
    const_iterator iterator(TNodeLinkList::const_iterator it) : mIt(it) {  }

    bool operator==(const_iterator other) { return (mIt == other.mIt);  }
    bool operator!=(const_iterator other) { return !(*this == other); }
    const_iterator& operator++() {
      ++mIt;
      return *this;
    }
    const_iterator& operator--() {
      --mIt;
      return *this;
    }

    const T* operator->() const { return TLinkList::Element_toValue(TNodeLinkList::const_iterator::operator->(mIt)); }
    const T& operator*() const {
      T* p = TLinkList::const_iterator::operator->();
      #line 586
      JUT_ASSERT(p!=0);
      return *p;
    }

  private:
    TNodeLinkList::const_iterator mIt;
  };

  iterator Find(const T* p) { return TNodeLinkList::Find(TLinkList::Element_toNode(p)); }
  iterator Erase( T* p) { return TNodeLinkList::Erase(Element_toNode(p)); }
  iterator Insert(iterator it, T* p) { return TNodeLinkList::Insert(it, Element_toNode(p)); }
  void Remove(T* p) { TNodeLinkList::Remove(TLinkList::Element_toNode(p)); }
  void Push_front(T* p) { Insert(begin(), p); }
  void Push_back(T* p) { Insert(end(), p); }

  T& front() {
    #line 642
    JUT_ASSERT(!empty());
    return *begin();
  }

  T& back() {
    #line 652
    JUT_ASSERT(!empty());
    iterator itEnd = end();
    --itEnd;
    return *itEnd;
  }

  iterator begin() { return TNodeLinkList::begin(); }
  const_iterator begin() const { return TNodeLinkList::begin(); }

  iterator end() { return TNodeLinkList::end(); }
  const_iterator end() const { return TNodeLinkList::end(); }

  static TLinkListNode* Element_toNode(T* p) {
    #line 753
    JUT_ASSERT(p!=0);
    return (TLinkListNode*)((char*)p + O);
  }

  static const TLinkListNode* Element_toNode(const T* p) {
    #line 758
    JUT_ASSERT(p!=0);
    return (const TLinkListNode*)((const char*)p + O);
  }

  static T* Element_toValue(TLinkListNode* p) {
    #line 763
    JUT_ASSERT(p!=0);
    return (T*)((char*)p - O);
  }

  static const T* Element_toValue(const TLinkListNode* p) {
    #line 763
    JUT_ASSERT(p!=0);
    return (const T*)((const char*)p - O);
  }
};

}

#endif
