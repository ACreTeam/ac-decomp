#include "JSystem/JGadget/linklist.h"

#include "MSL_CPP/algorithm.h"
#include "MSL_CPP/iterator.h"

namespace JGadget {

TNodeLinkList::~TNodeLinkList() {
  Confirm();
  clear();
  JGADGET_ASSERTWARN(empty());
  this->oNode_.clear_();
}

void TNodeLinkList::Initialize_() {
  this->size_ = 0;
  this->oNode_.pNext_ = &this->oNode_;
  this->oNode_.pPrev_ = &this->oNode_;
}

TNodeLinkList::iterator TNodeLinkList::erase(iterator it, iterator itEnd) {
  for (it; it != itEnd; ++it) {
    this->Erase(it.p_);
  }

  return itEnd;
}

TNodeLinkList::iterator TNodeLinkList::erase(TNodeLinkList::iterator it) {
  #line 102
  JUT_ASSERT(it.p_!=&oNode_);

  iterator itNext = it;
  ++itNext;

  return this->erase(it, itNext);
}

void TNodeLinkList::splice(TNodeLinkList::iterator it, TNodeLinkList& rSrc, TNodeLinkList::iterator itBegin, TNodeLinkList::iterator itEnd) {
  s32 dist = 0;

  if (this == &rSrc) {
    if (itBegin == itEnd) {
      return;
    }
  }
  else {
    dist = std::distance(itBegin, itEnd);

    if (dist == 0) {
      return;
    }
  }

  TLinkListNode* node_it = it.p_;
  TLinkListNode* node_beg = itBegin.p_;
  TLinkListNode* node_end = itEnd.p_;

  TLinkListNode* end_prev = node_end->pPrev_;
  TLinkListNode* beg_prev = node_beg->pPrev_;

  beg_prev->pNext_ = node_end;
  node_end->pPrev_ = beg_prev;
  rSrc.size_ -= dist;

  TLinkListNode* it_prev = node_it->pPrev_;

  it_prev->pNext_ = node_beg;
  node_beg->pPrev_ = it_prev;
  end_prev->pNext_ = node_it;
  node_it->pPrev_ = end_prev;

  this->size_ += dist;
}

void TNodeLinkList::splice(TNodeLinkList::iterator it, TNodeLinkList& rSrc, TNodeLinkList::iterator itSrc) {
  iterator itSrcNext = itSrc;
  ++itSrcNext;
  bool invalid = true;

  if (!(it == itSrc) && !(it == itSrcNext)) {
    invalid = false;
  }

  if (!invalid) {
    TLinkListNode& node = *itSrc;

    rSrc.Erase(&node);
    this->Insert(it, &node);
  }
}

void TNodeLinkList::splice(iterator it, TNodeLinkList& rSrc) {
  #line 146
  JUT_ASSERT(this!=&rSrc);
  this->splice(it, rSrc, rSrc.begin(), rSrc.end());
  JUT_ASSERT(rSrc.empty());
}

void TNodeLinkList::Remove(TLinkListNode* node) {
  this->remove_if(TPRIsEqual_pointer_(node));
}

template<typename Predicate>
void TNodeLinkList::Remove_if(Predicate predicate, TNodeLinkList& tList) {
  iterator itBeg = this->begin();
  iterator it = itBeg;

  while(!Iterator_isEnd_(it)) {
    if (predicate(*it) == true) {
      iterator itPrev = it;
      ++it;
      tList.splice(tList.end(), *this, itPrev);
    }
    else {
      ++it;
    }
  }
}

TNodeLinkList::iterator TNodeLinkList::Find(const TLinkListNode* node) {
  return std::find_if(this->begin(), this->end(), TPRIsEqual_pointer_(node));
}

TNodeLinkList::iterator TNodeLinkList::Insert(iterator it, TLinkListNode* p) {
  #line 300
  JUT_ASSERT(p!=0);
  TLinkListNode* pIt = it.p_;
  JUT_ASSERT(pIt!=0);
  
  TLinkListNode* pItPrev = pIt->pPrev_;
  JUT_ASSERT(pItPrev!=0);

  JUT_ASSERT(p->pNext_==NULL);
  JUT_ASSERT(p->pPrev_==NULL);

  p->pNext_ = pIt;
  p->pPrev_ = pItPrev;
  pIt->pPrev_ = p;
  pItPrev->pNext_ = p;
  this->size_++;

  return p;
}

TNodeLinkList::iterator TNodeLinkList::Erase(TLinkListNode* p) {
  #line 325
  JUT_ASSERT(!empty());
  JUT_ASSERT(p!=0);
  JUT_ASSERT(p!=&oNode_);
  TLinkListNode* pNext = p->pNext_;
  TLinkListNode* pPrev = p->pPrev_;
  JUT_ASSERT(pNext!=0);
  pNext->pPrev_ = pPrev;
  JUT_ASSERT(pPrev!=0);
  pPrev->pNext_ = pNext;
  this->size_--;
  p->clear_();
  return pNext;
}

bool TNodeLinkList::Confirm() const {
  u32 u = 0;
  const_iterator itEnd(this->end());
  
  #line 357
  JGADGET_EXIT(itEnd.p_==&oNode_)
  const_iterator it(this->begin());
  JGADGET_EXIT(it.p_==oNode_.pNext_); // #line 359

  for (it; it != itEnd; ++it, ++u) {
    JGADGET_EXIT(u<size()); // #line 362
    const TLinkListNode* pIt = it.p_;
    JUT_ASSERT(pIt!=0); // #line 364
    JGADGET_EXIT(pIt->pNext_->pPrev_==pIt); // #line 365
    JGADGET_EXIT(pIt->pPrev_->pNext_==pIt); // #line 366
  }
  if (it.p_ == &this->oNode_) {
    JGADGET_EXIT(u==size()); // #line 369
    return true;
  }
}

bool TNodeLinkList::Confirm_iterator(const_iterator it) const {
  const_iterator itCur(this->begin());
  const_iterator itEnd(this->end());
  for (itCur; itCur != itEnd; ++itCur) {
    if (itCur==it) {
      return true;
    }
  }

  JGADGET_EXIT(it==itEnd); // #line 383
  return true;
}

} // namespace JGadget

