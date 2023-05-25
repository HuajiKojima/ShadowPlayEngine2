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
        const char* m_memPosFile;                 // 8 Bytes
        uint32_t m_blockID;                       // 4 Bytes
        uint16_t m_memPosLine;                    // 1 Bytes
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
        std::cout << "structor" << std::endl;
    }

    SPHeapMemAllocatorD::~SPHeapMemAllocatorD()
    {
        std::cout << "destructor" << std::endl;
        delete p;
    }

    void *SPHeapMemAllocatorD::MemAllocate(uint64_t length, uint8_t isArray, const char* posFile, uint16_t posLine)
    {  
        SPHeapMemAllocatorDBlock* newMem = nullptr;
        newMem = (SPHeapMemAllocatorDBlock*)malloc(sizeof(SPHeapMemAllocatorDBlock) + length);
        newMem->SPHeapMemAllocatorDBlock::SPHeapMemAllocatorDBlock();
        newMem->m_trueMem = (void*)(newMem + 1);
        newMem->m_blockID = 1;
        newMem->m_prev = nullptr;
        newMem->m_next = nullptr;
        newMem->m_isArray = isArray;
        newMem->m_memPosFile = posFile;
        newMem->m_memPosLine = posLine;

        newMem->m_next = p->m_memBlocks;
        if (p->m_memBlocks != nullptr)
        {
            p->m_memBlocks->m_prev = newMem;
        }
        p->m_memBlocks = newMem;

        return newMem->m_trueMem;
    }

    void SPHeapMemAllocatorD::MemDeallocate(void *tgtMemPointer, uint8_t isArray)
    {
        if(p->m_memBlocks == nullptr)
        {
            // output log: No enough mem block to deallocate.
            return;
        }

        SPHeapMemAllocatorDBlock* blockPointer = p->m_memBlocks;
        while (blockPointer != nullptr)
        {
            if (blockPointer->m_trueMem == tgtMemPointer)
            {
                if (blockPointer->m_prev != nullptr) { 
                    blockPointer->m_prev->m_next = blockPointer->m_next;
                }
                else {
                    p->m_memBlocks = blockPointer->m_next;
                }
                if (blockPointer->m_next != nullptr) {
                    blockPointer->m_next->m_prev = blockPointer->m_prev;
                }

                free(blockPointer);
                break;
            }
            blockPointer = blockPointer->m_next;
        }
        return;
    }

    void SPHeapMemAllocatorD::AllocatorTerminator()
    {
        if ((p == nullptr) || (p->m_memBlocks == nullptr))
        {
            return;
        }
        SPHeapMemAllocatorDBlock* memBlock = p->m_memBlocks;
        while (memBlock != nullptr)
        {
            std::cout << "Mem not release, location is \"" << memBlock->m_memPosFile << "\"(" << memBlock->m_memPosLine << ")" << std::endl;
            p->m_memBlocks = memBlock->m_next;
            if (memBlock->m_next != nullptr) 
            {
                memBlock->m_next->m_prev = nullptr;
            }
            free(memBlock);
            memBlock = memBlock->m_next;
        }
        delete p;
    }

    // Release version
    SPHeapMemAllocatorR::SPHeapMemAllocatorR()
    {
        p = new SPHeapMemAllocatorRPrivate();
    }

    SPHeapMemAllocatorR::~SPHeapMemAllocatorR()
    {
    }

    void *SPHeapMemAllocatorR::MemAllocate(uint64_t length, uint8_t isArray, const char* posFile, uint16_t posLine)
    {
        return nullptr;
    }

    void SPHeapMemAllocatorR::MemDeallocate(void *tgtMemPointer, uint8_t isArray)
    {
    }

    SPHeapMemAllocator *SPHeapMemAllocatorFactory::GetAllocator()
    {
        static bool isAllocatorCreate = false;
        static SPHeapMemAllocator* allocator = nullptr;
        if(isAllocatorCreate)
        {
            return allocator;
        }
        #ifdef SHADOWPLAY_DEBUG
            allocator = new SPHeapMemAllocatorD();
        #else
            allocator = new SPHeapMemAllocatorR();
        #endif
        isAllocatorCreate = true;
        return allocator;
    }
}
