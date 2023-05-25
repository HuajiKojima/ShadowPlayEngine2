#pragma once
#include <SPGlobal.h>
namespace ShadowPlay
{
    struct SPHeapMemAllocatorDPrivate;
    struct SPHeapMemAllocatorRPrivate;

    class SPHeapMemAllocator
    {
    public:
        virtual void* MemAllocate(uint64_t length, uint8_t isArray, const char* posFile, uint16_t posLine) = 0;
        virtual void MemDeallocate(void* tgtMemPointer, uint8_t isArray) = 0;
        virtual void AllocatorTerminator() = 0;
    };

    // Debug version
    class SHADOWPLAY_API SPHeapMemAllocatorD: public SPHeapMemAllocator
    {
    public:
        SPHeapMemAllocatorD();
        ~SPHeapMemAllocatorD();

        virtual void* MemAllocate(uint64_t length, uint8_t isArray, const char* posFile, uint16_t posLine);
        virtual void MemDeallocate(void* tgtMemPointer, uint8_t isArray = false);
        virtual void AllocatorTerminator();
    private:
        SPHeapMemAllocatorDPrivate* p;
    };

    // Release version
    class SHADOWPLAY_API SPHeapMemAllocatorR: public SPHeapMemAllocator
    {
    public:
        SPHeapMemAllocatorR();
        ~SPHeapMemAllocatorR();

        virtual void* MemAllocate(uint64_t length, uint8_t isArray, const char* posFile, uint16_t posLine);
        virtual void MemDeallocate(void* tgtMemPointer, uint8_t isArray);
    private:
        SPHeapMemAllocatorRPrivate* p;
    };

    class SHADOWPLAY_API SPHeapMemAllocatorFactory
    {
    public:
        static SPHeapMemAllocator* GetAllocator(); 
    };
}

template <class T>
inline void HeapMemAllocate(T* &pointer, const char* posFile, uint16_t posLine)
{
    ShadowPlay::SPHeapMemAllocator* allocator = ShadowPlay::SPHeapMemAllocatorFactory::GetAllocator();
    pointer = (T*)(allocator->MemAllocate(sizeof(T), false, posFile, posLine));
}

template <class T>
inline void HeapMemDeallocate(T* &pointer)
{
    ShadowPlay::SPHeapMemAllocator* allocator = ShadowPlay::SPHeapMemAllocatorFactory::GetAllocator();
    allocator->MemDeallocate(pointer, false);
}

template <class T>
inline void HeapArrayMemAllocate(T* &pointer, const char* posFile, uint16_t posLine)
{

}

template <class T>
inline void HeapArrayMemDeallocate(T* &pointer)
{

}

#define SHADOWPLAY_ALLOC_HEAPMEM(pointer, type)  \
    HeapMemAllocate<type>(pointer, __FILE__, __LINE__);\
    pointer->type::type();

#define SHADOWPLAY_DEALLOC_HEAPMEM(pointer, type) \
    pointer->type::~type(); \
    HeapMemDeallocate<type>(pointer);

#define SHADOWPLAY_ALLOC_ARR_HEAPMEM(pointer)

#define SHADOWPLAY_DEALLOC_ARR_HEAPMEM(pointer)