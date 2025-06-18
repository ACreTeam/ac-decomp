#include "JSystem/JGadget/linklist.h"

#include "MSL_CPP/algorithm.h"
#include "MSL_CPP/iterator.h"

namespace JGadget {

TNodeLinkList::~TNodeLinkList() {
#if DEBUG
  Confirm();
  clear();
#endif
  JGADGET_ASSERTWARN(empty());
  //this->oNode_.clear_();
}

TNodeLinkList::iterator TNodeLinkList::erase(iterator it, iterator itEnd) {
  TLinkListNode* cur = it.p_;
  TLinkListNode* end = itEnd.p_;
  TLinkListNode* next;

  for (; cur != end; cur = next) {
    next = cur->pNext_;
    this->Erase(cur);
  }

  return itEnd;
}

TNodeLinkList::iterator TNodeLinkList::erase(TNodeLinkList::iterator it) {
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

  if ((it == itSrc) || (it == itSrcNext)) {
      return;
  }
  else {
    TLinkListNode* const node = &*itSrc;

    rSrc.Erase(node);
    this->Insert(it, node);
  }
}

void TNodeLinkList::splice(iterator it, TNodeLinkList& rSrc) {
  JUT_ASSERT(this!=&rSrc);
  this->splice(it, rSrc, rSrc.begin(), rSrc.end());
  JUT_ASSERT(rSrc.empty());
}

TNodeLinkList::iterator TNodeLinkList::Find(const TLinkListNode* node) {
  return std::find_if(this->begin(), this->end(), TPRIsEqual_pointer_<TLinkListNode>(node));
}

#undef NULL
#define NULL 0
    
TNodeLinkList::iterator TNodeLinkList::Insert(iterator it, TLinkListNode* p) {
  JUT_ASSERT(p!=0);
  TLinkListNode* pIt = it.p_;
  JUT_ASSERT(pIt!=0);
  
  TLinkListNode* pItPrev = pIt->pPrev_;
  JUT_ASSERT(pItPrev!=0);

  JGADGET_ASSERTWARN(p->pNext_==NULL);
  JGADGET_ASSERTWARN(p->pPrev_==NULL);

  p->pNext_ = pIt;
  p->pPrev_ = pItPrev;
  pIt->pPrev_ = p;
  pItPrev->pNext_ = p;
  this->size_++;

  return p;
}

#undef NULL
#define NULL (void*)0;

TNodeLinkList::iterator TNodeLinkList::Erase(TLinkListNode* p) {
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
  //p->clear_();
  return pNext;
}

void TNodeLinkList::Remove(TLinkListNode* node) {
  this->remove_if(TPRIsEqual_pointer_<TLinkListNode>(node));
}

bool TNodeLinkList::Confirm() const {
  u32 u = 0;
  const_iterator itEnd = this->end();
  
  JGADGET_EXITWARN(itEnd.p_==&oNode_);
  const_iterator it = this->begin();
  JGADGET_EXITWARN(it.p_==oNode_.pNext_);

  for (; it != itEnd; ++it, ++u) {
    JGADGET_EXITWARN(u<size());
    const TLinkListNode* pIt = it.p_;
    JUT_ASSERT(pIt!=0);
    JGADGET_EXITWARN(pIt->pNext_->pPrev_==pIt);
    JGADGET_EXITWARN(pIt->pPrev_->pNext_==pIt);
  }

  JGADGET_EXITWARN(it.p_==&oNode_);
  JGADGET_EXITWARN(u==size());
  return true;
}

bool TNodeLinkList::Confirm_iterator(const_iterator it) const {
  const_iterator itBegin = begin();
  const_iterator itEnd = end();

  while (itBegin != itEnd) {
    if (itBegin == it) {
      return true;
    }

    ++itBegin;
  }

  JGADGET_EXITWARN(it==itEnd);

  return true;
}

} // namespace JGadget
