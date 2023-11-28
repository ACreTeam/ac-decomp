#ifndef JGADGET_LINK_H
#define JGADGET_LINK_H

#include "types.h"

#include "JSystem/JUtility/JUTAssertion.h"

namespace JGadget {

#define JGADGET_ASSERTWARN(cond)          \
  if ((cond) == false)                    \
  {                                       \
    /*JGadget_outMessage msg(&warning);*/ \
    /*msg << (#cond);*/                   \
  }

#define JGADGET_EXIT(cond)                \
  if ((cond) == false)                    \
  {                                       \
    /*JGadget_outMessage msg(&warning);*/ \
    /*msg << (#cond);*/                   \
    return false;                         \
  }

/* TODO: this definitely has a better place to live */
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

class TLinkListNode {
public:
  TLinkListNode() {
    this->pNext_ = nullptr;
    this->pPrev_ = nullptr;
  }

  ~TLinkListNode() {
    JGADGET_ASSERTWARN(pNext_==NULL);
    JGADGET_ASSERTWARN(pPrev_==NULL);
  }

  TLinkListNode* getNext() const {
    return this->pNext_;
  }

  TLinkListNode* getPrev() const {
    return this->pPrev_;
  }

  void clear_() {
    this->pNext_ = nullptr;
    this->pPrev_ = nullptr;
  }

  TLinkListNode* pNext_;
  TLinkListNode* pPrev_;
};

class TNodeLinkList {
public:
  TNodeLinkList() { Initialize_(); }
  ~TNodeLinkList();

  class iterator {
  public:
    iterator() { this->p_ = nullptr; }
    iterator(TLinkListNode* node) { this->p_ = node; }
    iterator(const iterator& it) { this->p_ = it.p_; }

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
    const_iterator(const const_iterator& it) { this->p_ = it.p_; }

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
  template <typename Predicate> void Remove_if(Predicate predicate, TNodeLinkList& tList);

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
  void Initialize_() {
    this->size_ = 0;
    this->oNode_.pNext_ = &this->oNode_;
    this->oNode_.pPrev_ = &this->oNode_;
  }
  bool Iterator_isEnd_(const_iterator it) const { return &this->oNode_ == it.p_; }

  s32 size_;
  TLinkListNode oNode_;
};

bool operator==(TNodeLinkList::iterator lhs, TNodeLinkList::iterator rhs) { return lhs.p_ == rhs.p_; }
bool operator!=(TNodeLinkList::iterator lhs, TNodeLinkList::iterator rhs) { return !(lhs == rhs); }

bool operator==(TNodeLinkList::const_iterator lhs, TNodeLinkList::const_iterator rhs) { return lhs.p_ == rhs.p_; }
bool operator!=(TNodeLinkList::const_iterator lhs, TNodeLinkList::const_iterator rhs) { return !(lhs == rhs); }

}

#endif
