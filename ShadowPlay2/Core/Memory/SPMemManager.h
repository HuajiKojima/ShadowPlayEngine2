#include <SPGlobal.h>
namespace ShadowPlay
{
    struct SPHeapMemAllocatorDPrivate;
    struct SPHeapMemAllocatorRPrivate;

    class SPHeapMemAllocator
    {
    public:
        virtual void* MemAllocate(uint64_t length, uint8_t isArray) = 0;
        virtual void MemDeallocate(void* tgtMemPointer, uint8_t isArray) = 0;

    };

    // Debug version
    class SHADOWPLAY_API SPHeapMemAllocatorD: public SPHeapMemAllocator
    {
    public:
        SPHeapMemAllocatorD();
        ~SPHeapMemAllocatorD();

        virtual void* MemAllocate(uint64_t length, uint8_t isArray);
        virtual void MemDeallocate(void* tgtMemPointer, uint8_t isArray = false);
    private:
        SPHeapMemAllocatorDPrivate* p;
    };

    // Release version
    class SHADOWPLAY_API SPHeapMemAllocatorR: public SPHeapMemAllocator
    {
    public:
        SPHeapMemAllocatorR();
        ~SPHeapMemAllocatorR();

        virtual void* MemAllocate(uint64_t length, uint8_t isArray);
        virtual void MemDeallocate(void* tgtMemPointer, uint8_t isArray);
    private:
        SPHeapMemAllocatorRPrivate* p;
    };
}