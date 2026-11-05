#ifndef JSULIST_H
#define JSULIST_H

#include "types.h"

class JSUPtrLink;

class JSUPtrList
{
public:
    JSUPtrList()
    {
        initiate();
    }

    JSUPtrList(bool);
    ~JSUPtrList();

    void initiate();
    void setFirst(JSUPtrLink *);
    bool append(JSUPtrLink *);
    bool prepend(JSUPtrLink *);
    bool insert(JSUPtrLink *, JSUPtrLink *);
    bool remove(JSUPtrLink *);
    JSUPtrLink *getNthLink(u32 idx) const;

    JSUPtrLink *getFirstLink() const { return mHead; }
    JSUPtrLink *getLastLink() const { return mTail; }
    u32 getNumLinks() const { return mLinkCount; }

    JSUPtrLink *mHead; // _0
    JSUPtrLink *mTail; // _4
    u32 mLinkCount;    // _8
};

class JSUPtrLink
{
public:
    JSUPtrLink(void *);
    ~JSUPtrLink();

    void *getObjectPtr() const { return mData; }
    JSUPtrList *getList() const { return mPtrList; }
    JSUPtrLink *getNext() const { return mNext; }
    JSUPtrLink *getPrev() const { return mPrev; }

    void *mData;          // _0
    JSUPtrList *mPtrList; // _4
    JSUPtrLink *mPrev;    // _8
    JSUPtrLink *mNext;    // _C
};

template <class T>
class JSULink; // friend class? i'm C++ noob

template <class T>
class JSUList : public JSUPtrList
{
public:
    JSUList(bool thing) : JSUPtrList(thing)
    {
    }
    JSUList() : JSUPtrList()
    {
    }

    void initiate() { JSUPtrList::initiate(); }
    bool append(JSULink<T> *link) { return JSUPtrList::append((JSUPtrLink *)link); }
    bool prepend(JSULink<T> *link) { return JSUPtrList::prepend((JSUPtrLink *)link); }
    bool insert(JSULink<T> *before, JSULink<T> *link) { return JSUPtrList::insert((JSUPtrLink *)before, (JSUPtrLink *)link); }
    bool remove(JSULink<T> *link) { return JSUPtrList::remove((JSUPtrLink *)link); }

    JSULink<T> *getFirst() const { return (JSULink<T> *)getFirstLink(); }
    JSULink<T> *getLast() const { return (JSULink<T> *)getLastLink(); }
    JSULink<T> *getNth(u32 index) const { return (JSULink<T> *)getNthLink(index); }
    JSULink<T> *getEnd() const { return nullptr; }

    u32 getNumLinks() const { return mLinkCount; }
};

template <typename T>
class JSUListIterator
{
public:
    JSUListIterator()
        : mLink(nullptr)
    {
    }
    JSUListIterator(JSULink<T> *link)
        : mLink(link)
    {
    }
    JSUListIterator(JSUList<T> *list)
        : mLink(list->getFirst())
    {
    }

    void goNext() {
        mLink = mLink->getNext();
    }

    JSUListIterator<T> &operator=(JSULink<T> *link)
    {
        mLink = link;
        return *this;
    }

    T *getObject() const { return mLink->getObject(); }

    bool isAvailable() { return mLink != nullptr; }
    bool operator==(const JSULink<T> *other) const { return mLink == other; }
    bool operator!=(const JSULink<T> *other) const { return mLink != other; }
    bool operator==(const JSUListIterator<T> &other) const { return mLink == other.mLink; }
    bool operator!=(const JSUListIterator<T> &other) const { return mLink != other.mLink; }

    JSUListIterator<T> operator++(int)
    {
        JSUListIterator<T> prev = *this;
        mLink = mLink->getNext();
        return prev;
    }

    JSUListIterator<T> &operator++()
    {
        mLink = mLink->getNext();
        return *this;
    }

    JSUListIterator<T> operator--(int)
    {
        JSUListIterator<T> prev = *this;
        mLink = mLink->getPrev();
        return prev;
    }

    JSUListIterator<T> &operator--()
    {
        mLink = mLink->getPrev();
        return *this;
    }

    // Investigate where and if this actually exists
    // T &operator*() { return *getObject(); }

    T *operator->() const { return mLink->getObject(); }

    // private:
    JSULink<T> *mLink;
};

template <class T>
class JSULink : public JSUPtrLink
{
public:
    JSULink(T *pData) : JSUPtrLink(pData) {}

    T *getObject() const { return (T *)mData; }
    JSUList<T> *getSupervisor() const { return (JSUList<T> *)mPtrList; }
    JSULink<T> *getNext() const { return (JSULink<T> *)mNext; }
    JSULink<T> *getPrev() const { return (JSULink<T> *)mPrev; }

    ~JSULink() {}
};

template <typename T>
class JSUTree : public JSUList<T>, public JSULink<T>
{
public:
    JSUTree(T *owner) : JSUList<T>(), JSULink<T>(owner) {}
    ~JSUTree() {}

    bool appendChild(JSUTree<T> *child) { return append(child); }
    bool prependChild(JSUTree<T> *child) { return prepend(child); }
    bool removeChild(JSUTree<T> *child) { return remove(child); }
    bool insertChild(JSUTree<T> *before, JSUTree<T> *child) { return insert(before, child); }

    JSUTree<T> *getEndChild() const { return nullptr; }
    JSUTree<T> *getFirstChild() const { return (JSUTree<T> *)getFirstLink(); }
    JSUTree<T> *getLastChild() const { return (JSUTree<T> *)getLastLink(); }
    JSUTree<T> *getNextChild() const { return (JSUTree<T> *)mNext; }
    JSUTree<T> *getPrevChild() const { return (JSUTree<T> *)mPrev; }
    u32 getNumChildren() const { return mLinkCount; } // In TP Debug getNumLinks() gets called here, however that kills something in JKRHeap::find(inline depth?)
    T *getObject() const { return (T *)mData; }
    JSUTree<T> *getParent() const { return (JSUTree<T> *)mPtrList; }
};

template <typename T>
class JSUTreeIterator
{
public:
    JSUTreeIterator() : mTree(nullptr) {}
    JSUTreeIterator(JSUTree<T> *tree) : mTree(tree) {}

    JSUTreeIterator<T> &operator=(JSUTree<T> *tree)
    {
        mTree = tree;
        return *this;
    }

    T *getObject() const { return mTree->getObject(); }

    bool operator==(JSUTree<T> *other) { return mTree == other; }

    bool operator!=(const JSUTree<T> *other) const { return mTree != other; }

    JSUTreeIterator<T> operator++(int)
    {
        JSUTreeIterator<T> prev = *this;
        mTree = mTree->getNextChild();
        return prev;
    }

    JSUTreeIterator<T> &operator++()
    {
        mTree = mTree->getNextChild();
        return *this;
    }

    T *operator*() const { return getObject(); }

    T *operator->() const { return mTree->getObject(); }

private:
    JSUTree<T> *mTree;
};

#endif /* JSULIST_H */
