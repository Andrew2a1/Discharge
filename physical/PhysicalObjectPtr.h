#if !defined(PHYSICAL_OBJECT_POINTER)
#define PHYSICAL_OBJECT_POINTER

#include <memory>

class PhysicalObject;
typedef std::shared_ptr<PhysicalObject> PhysicalObjectPtr;

class ElectricCharge;
typedef std::shared_ptr<ElectricCharge> ElectricChargePtr;

#endif // PHYSICAL_OBJECT_POINTER
