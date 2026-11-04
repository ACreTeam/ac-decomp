#ifndef JSULIST_H
#define JSULIST_H

#include "types.h"

class JSUPtrLink;

class JSUPtrList {
  public:
    JSUPtrList() {
        initiate();
    }

    JSUPtrList(bool);
    ~JSUPtrList();

    void initiate();
    void setFirst(JSUPtrLink*);
    bool append(JSUPtrLink*);
    bool prepend(JSUPtrLink*);
    bool insert(JSUPtrLink*, JSUPtrLink*);
    bool remove(JSUPtrLink*);
    JSUPtrLink* getNthLink(u32 idx) const;

    JSUPtrLink* getFirstLink() const {
        return mHead;
    }
    JSUPtrLink* getLastLink() const {
        return mTail;
    }
    u32 getNumLinks() const {
        return mLinkCount;
    }

    JSUPtrLink* mHead; // _0
    JSUPtrLink* mTail; // _4
    u32 mLinkCount;    // _8
};

class JSUPtrLink {
  public:
    JSUPtrLink(void*);
    ~JSUPtrLink();

    void* getObjectPtr() const {
        return mData;
    }
    JSUPtrList* getList() const {
        return mPtrList;
    }
    JSUPtrLink* getNext() const {
        return mNext;
    }
    JSUPtrLink* getPrev() const {
        return mPrev;
    }

    void* mData;          // _0
    JSUPtrList* mPtrList; // _4
    JSUPtrLink* mPrev;    // _8
    JSUPtrLink* mNext;    // _C
};

template <class T> class JSULink; // friend class? i'm C++ noob

template <class T> class JSUList : public JSUPtrList {
  public:
    JSUList(bool thing) : JSUPtrList(thing) {
    }
    JSUList() : JSUPtrList() {
    }

    bool append(JSULink<T>* link) {
        return JSUPtrList::append((JSUPtrLink*)link);
    }
    bool prepend(JSULink<T>* link) {
        return JSUPtrList::prepend((JSUPtrLink*)link);
    }
    bool insert(JSULink<T>* before, JSULink<T>* link) {
        return JSUPtrList::insert((JSUPtrLink*)before, (JSUPtrLink*)link);
    }
    bool remove(JSULink<T>* link) {
        return JSUPtrList::remove((JSUPtrLink*)link);
    }

    JSULink<T>* getFirst() const {
        return (JSULink<T>*)getFirstLink();
    }
    JSULink<T>* getLast() const {
        return (JSULink<T>*)getLastLink();
    }
    JSULink<T>* getEnd() const {
        return nullptr;
    }

    u32 getNumLinks() const {
        return mLinkCount;
    }
};

template <typename T> class JSUListIterator {
  public:
    JSUListIterator() : mLink(nullptr) {
    }
    JSUListIterator(JSULink<T>* link) : mLink(link) {
    }
    JSUListIterator(JSUList<T>* list) : mLink(list->getFirst()) {
    }

    JSUListIterator<T>& operator=(JSULink<T>* link) {
        this->mLink = link;
        return *this;
    }

    T* getObject() {
        return this->mLink->getObject();
    }

    bool operator==(JSULink<T> const* other) const {
        return this->mLink == other;
    }
    bool operator!=(JSULink<T> const* other) const {
        return this->mLink != other;
    }
    bool operator==(JSUListIterator<T> const& other) const {
        return this->mLink == other.mLink;
    }
    bool operator!=(JSUListIterator<T> const& other) const {
        return this->mLink != other.mLink;
    }

    JSUListIterator<T> operator++(int) {
        JSUListIterator<T> prev = *this;
        this->mLink = this->mLink->getNext();
        return prev;
    }

    JSUListIterator<T>& operator++() {
        this->mLink = this->mLink->getNext();
        return *this;
    }

    JSUListIterator<T> operator--(int) {
        JSUListIterator<T> prev = *this;
        this->mLink = this->mLink->getPrev();
        return prev;
    }

    JSUListIterator<T>& operator--() {
        this->mLink = this->mLink->getPrev();
        return *this;
    }

    T& operator*() {
        return *this->getObject();
    }

    T* operator->() {
        return this->getObject();
    }

    // private:
    JSULink<T>* mLink;
};

template <class T> class JSULink : public JSUPtrLink {
  public:
    JSULink(void* pData) : JSUPtrLink(pData) {
    }

    T* getObject() const {
        return (T*)mData;
    }
    JSUList<T>* getList() const {
        return (JSUList<T>*)JSUPtrLink::getList();
    } // fabricated, offcial name: getSupervisor
    JSULink<T>* getNext() const {
        return (JSULink<T>*)JSUPtrLink::getNext();
    }
    JSULink<T>* getPrev() const {
        return (JSULink<T>*)JSUPtrLink::getPrev();
    }

    ~JSULink() {
    }
};

template <typename T> // TODO: most of these inlines are probably wrong: rework
class JSUTree : public JSUList<T>, public JSULink<T> {
  public:
    JSUTree(T* owner) : JSUList<T>(), JSULink<T>(owner) {
    }
    ~JSUTree() {
    }

    bool appendChild(JSUTree<T>* child) {
        return this->append(child);
    }
    bool prependChild(JSUTree<T>* child) {
        return this->prepend(child);
    }
    bool removeChild(JSUTree<T>* child) {
        return this->remove(child);
    }
    bool insertChild(JSUTree<T>* before, JSUTree<T>* child) {
        return this->insert(before, child);
    }

    JSUTree<T>* getEndChild() const {
        return nullptr;
    }
    JSUTree<T>* getFirstChild() const {
        return (JSUTree<T>*)this->getFirstLink();
    }
    JSUTree<T>* getLastChild() const {
        return (JSUTree<T>*)this->getLast();
    }
    JSUTree<T>* getNextChild() const {
        return (JSUTree<T>*)this->mNext;
    }
    JSUTree<T>* getPrevChild() const {
        return (JSUTree<T>*)this->getPrev();
    }
    u32 getNumChildren() const {
        return this->mLinkCount;
    }
    T* getObject() const {
        return (T*)this->mData;
    }
    JSUTree<T>* getParent() const {
        return (JSUTree<T>*)this->mPtrList;
    }
};

template <typename T> class JSUTreeIterator {
  public:
    JSUTreeIterator() : mTree(nullptr) {
    }
    JSUTreeIterator(JSUTree<T>* tree) : mTree(tree) {
    }

    JSUTreeIterator<T>& operator=(JSUTree<T>* tree) {
        this->mTree = tree;
        return *this;
    }

    T* getObject() const {
        return mTree->getObject();
    }

    bool operator==(JSUTree<T>* other) {
        return this->mTree == other;
    }

    bool operator!=(const JSUTree<T>* other) const {
        return this->mTree != other;
    }

    JSUTreeIterator<T> operator++(int) {
        JSUTreeIterator<T> prev = *this;
        this->mTree = this->mTree->getNextChild();
        return prev;
    }

    JSUTreeIterator<T>& operator++() {
        this->mTree = this->mTree->getNextChild();
        return *this;
    }

    T& operator*() {
        return *this->getObject();
    }

    T* operator->() const {
        return mTree->getObject();
    }

  private:
    JSUTree<T>* mTree;
};

#endif /* JSULIST_H */
