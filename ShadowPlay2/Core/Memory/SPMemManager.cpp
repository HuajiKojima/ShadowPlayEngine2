#include "ShadowPreCompileHeader.h"
#include "SPMemManager.h"

namespace ShadowPlay
{
    struct SPHeapMemAllocatorDBlock
    {
        SPHeapMemAllocatorDBlock()
        {
            m_prev = nullptr;
            m_next = nullptr;
            m_trueMem = nullptr; 
            m_blockID = 0;    
            m_isArray = false; 
        }

        SPHeapMemAllocatorDBlock* m_prev;         // 8 Bytes
        SPHeapMemAllocatorDBlock* m_next;         // 8 Bytes
        void* m_trueMem;                          // 8 Bytes
        uint32_t m_blockID;                       // 4 Bytes
        uint8_t m_isArray;                        // 1 Bytes
    };
    

    struct SPHeapMemAllocatorDPrivate
    {
        SPHeapMemAllocatorDBlock* m_memBlocks = nullptr;

    };
    struct SPHeapMemAllocatorRPrivate
    {};

    SPHeapMemAllocatorD::SPHeapMemAllocatorD()
    {
        p = new SPHeapMemAllocatorDPrivate();
    }

    SPHeapMemAllocatorD::~SPHeapMemAllocatorD()
    {
        delete p;
    }

    void *SPHeapMemAllocatorD::MemAllocate(uint64_t length, uint8_t isArray)
    {  
        SPHeapMemAllocatorDBlock* newMem = nullptr;
        newMem = (SPHeapMemAllocatorDBlock*)malloc(sizeof(SPHeapMemAllocatorDBlock) + length);
        newMem->SPHeapMemAllocatorDBlock::SPHeapMemAllocatorDBlock();
        newMem->m_trueMem = (void*)(newMem + 1);
        newMem->m_blockID = 1;
        newMem->m_prev = nullptr;
        newMem->m_next = nullptr;
        newMem->m_isArray = isArray;
        return newMem->m_trueMem;
    }

    void SPHeapMemAllocatorD::MemDeallocate(void *tgtMemPointer, uint8_t isArray)
    {
    }


    // Release version
    SPHeapMemAllocatorR::SPHeapMemAllocatorR()
    {
        p = new SPHeapMemAllocatorRPrivate();
    }

    SPHeapMemAllocatorR::~SPHeapMemAllocatorR()
    {
    }

    void *SPHeapMemAllocatorR::MemAllocate(uint64_t length, uint8_t isArray)
    {
        return nullptr;
    }

    void SPHeapMemAllocatorR::MemDeallocate(void *tgtMemPointer, uint8_t isArray)
    {
    }
}
