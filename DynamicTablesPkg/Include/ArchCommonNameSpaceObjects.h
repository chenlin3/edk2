/** @file

  Copyright (c) 2024, Arm Limited. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

  @par Glossary:
    - Cm or CM   - Configuration Manager
    - Obj or OBJ - Object
    - Std or STD - Standard
**/

#ifndef ARCH_COMMON_NAMESPACE_OBJECTS_H_
#define ARCH_COMMON_NAMESPACE_OBJECTS_H_

#include <AcpiObjects.h>
#include <StandardNameSpaceObjects.h>

/** The EARCH_COMMON_OBJECT_ID enum describes the Object IDs
    in the Arch Common Namespace
*/
typedef enum ArchCommonObjectID {
  EArchCommonObjReserved,                       ///<  0 - Reserved
  EArchCommonObjPowerManagementProfileInfo,     ///<  1 - Power Management Profile Info
  EArchCommonObjSerialPortInfo,                 ///<  2 - Generic Serial Port Info
  EArchCommonObjConsolePortInfo,                ///<  3 - Serial Console Port Info
  EArchCommonObjSerialDebugPortInfo,            ///<  4 - Serial Debug Port Info
  EArchCommonObjHypervisorVendorIdentity,       ///<  5 - Hypervisor Vendor Id
  EArchCommonObjFixedFeatureFlags,              ///<  6 - Fixed feature flags for FADT
  EArchCommonObjCmRef,                          ///<  7 - CM Object Reference
  EArchCommonObjPciConfigSpaceInfo,             ///<  8 - PCI Configuration Space Info
  EArchCommonObjPciAddressMapInfo,              ///<  9 - Pci Address Map Info
  EArchCommonObjPciInterruptMapInfo,            ///< 10 - Pci Interrupt Map Info
  EArchCommonObjMemoryAffinityInfo,             ///< 11 - Memory Affinity Info
  EArchCommonObjDeviceHandleAcpi,               ///< 12 - Device Handle Acpi
  EArchCommonObjDeviceHandlePci,                ///< 13 - Device Handle Pci
  EArchCommonObjGenericInitiatorAffinityInfo,   ///< 14 - Generic Initiator Affinity
  EArchCommonObjLpiInfo,                        ///< 15 - Lpi Info
  EArchCommonObjProcHierarchyInfo,              ///< 16 - Processor Hierarchy Info
  EArchCommonObjCacheInfo,                      ///< 17 - Cache Info
  EArchCommonObjCpcInfo,                        ///< 18 - Continuous Performance Control Info
  EArchCommonObjPccSubspaceType0Info,           ///< 19 - Pcc Subspace Type 0 Info
  EArchCommonObjPccSubspaceType1Info,           ///< 20 - Pcc Subspace Type 1 Info
  EArchCommonObjPccSubspaceType2Info,           ///< 21 - Pcc Subspace Type 2 Info
  EArchCommonObjPccSubspaceType3Info,           ///< 22 - Pcc Subspace Type 3 Info
  EArchCommonObjPccSubspaceType4Info,           ///< 23 - Pcc Subspace Type 4 Info
  EArchCommonObjPccSubspaceType5Info,           ///< 24 - Pcc Subspace Type 5 Info
  EArchCommonObjPsdInfo,                        ///< 25 - P-State Dependency (PSD) Info
  EArchCommonObjMax
} EARCH_COMMON_OBJECT_ID;

#pragma pack(1)

/** A structure that describes the
    Power Management Profile Information for the Platform.

    ID: EArchCommonObjPowerManagementProfileInfo
*/
typedef struct CmArchCommonPowerManagementProfileInfo {
  /** This is the Preferred_PM_Profile field of the FADT Table
      described in the ACPI Specification
  */
  UINT8    PowerManagementProfile;
} CM_ARCH_COMMON_POWER_MANAGEMENT_PROFILE_INFO;

/** A structure that describes the
    Serial Port information for the Platform.

    ID: EArchCommonObjConsolePortInfo or
        EArchCommonObjSerialDebugPortInfo or
        EArchCommonObjSerialPortInfo
*/
typedef struct EArchCommonSerialPortInfo {
  /// The physical base address for the serial port
  UINT64    BaseAddress;

  /** The serial port interrupt.
      0 indicates that the serial port does not
      have an interrupt wired.
  */
  UINT32    Interrupt;

  /// The serial port baud rate
  UINT64    BaudRate;

  /// The serial port clock
  UINT32    Clock;

  /// Serial Port subtype
  UINT16    PortSubtype;

  /// The Base address length
  UINT64    BaseAddressLength;

  /// The access size
  UINT8     AccessSize;
} CM_ARCH_COMMON_SERIAL_PORT_INFO;

/** A structure that describes the
    Hypervisor Vendor ID information for the Platform.

    ID: EArchCommonObjHypervisorVendorIdentity
*/
typedef struct CmArchCommonHypervisorVendorIdentity {
  /// The hypervisor Vendor ID
  UINT64    HypervisorVendorId;
} CM_ARCH_COMMON_HYPERVISOR_VENDOR_ID;

/** A structure that describes the
    Fixed feature flags for the Platform.

    ID: EArchCommonObjFixedFeatureFlags
*/
typedef struct CmArchCommonFixedFeatureFlags {
  /// The Fixed feature flags
  UINT32    Flags;
} CM_ARCH_COMMON_FIXED_FEATURE_FLAGS;

/** A structure that describes a reference to another Configuration Manager
    object.

    This is useful for creating an array of reference tokens. The framework
    can then query the configuration manager for these arrays using the
    object ID EArchCommonObjCmRef.

    This can be used is to represent one-to-many relationships between objects.

    ID: EArchCommonObjCmRef
*/
typedef struct CmArchCommonObjRef {
  /// Token of the CM object being referenced
  CM_OBJECT_TOKEN    ReferenceToken;
} CM_ARCH_COMMON_OBJ_REF;

/** A structure that describes the
    PCI Configuration Space information for the Platform.

    ID: EArchCommonObjPciConfigSpaceInfo
*/
typedef struct CmArchCommonPciConfigSpaceInfo {
  /// The physical base address for the PCI segment
  UINT64             BaseAddress;

  /// The PCI segment group number
  UINT16             PciSegmentGroupNumber;

  /// The start bus number
  UINT8              StartBusNumber;

  /// The end bus number
  UINT8              EndBusNumber;

  /// Optional field: Reference Token for address mapping.
  /// Token identifying a CM_ARCH_COMMON_OBJ_REF structure.
  CM_OBJECT_TOKEN    AddressMapToken;

  /// Optional field: Reference Token for interrupt mapping.
  /// Token identifying a CM_ARCH_COMMON_OBJ_REF structure.
  CM_OBJECT_TOKEN    InterruptMapToken;
} CM_ARCH_COMMON_PCI_CONFIG_SPACE_INFO;

/** A structure that describes a PCI Address Map.

  The memory-ranges used by the PCI bus are described by this object.

  ID: EArchCommonObjPciAddressMapInfo
*/
typedef struct CmArchCommonPciAddressMapInfo {
  /** Pci address space code

  Available values are:
   - 0: Configuration Space
   - 1: I/O Space
   - 2: 32-bit-address Memory Space
   - 3: 64-bit-address Memory Space
  */
  UINT8     SpaceCode;

  /// PCI address
  UINT64    PciAddress;

  /// Cpu address
  UINT64    CpuAddress;

  /// Address size
  UINT64    AddressSize;
} CM_ARCH_COMMON_PCI_ADDRESS_MAP_INFO;

/** A structure that describes the
    Generic Interrupts.
*/
typedef struct CmArchCommonGenericInterrupt {
  /// Interrupt number
  UINT32    Interrupt;

  /// Flags
  /// BIT0: 0: Interrupt is Level triggered
  ///       1: Interrupt is Edge triggered
  /// BIT1: 0: Interrupt is Active high
  ///       1: Interrupt is Active low
  UINT32    Flags;
} CM_ARCH_COMMON_GENERIC_INTERRUPT;

/** A structure that describes a PCI Interrupt Map.

  The legacy PCI interrupts used by PCI devices are described by this object.

  Cf Devicetree Specification - Release v0.3
  s2.4.3 "Interrupt Nexus Properties"

  ID: EArchCommonObjPciInterruptMapInfo
*/
typedef struct CmArchCommonPciInterruptMapInfo {
  /// Pci Bus.
  /// Value on 8 bits (max 255).
  UINT8    PciBus;

  /// Pci Device.
  /// Value on 5 bits (max 31).
  UINT8    PciDevice;

  /** PCI interrupt

  ACPI bindings are used:
  Cf. ACPI 6.4, s6.2.13 _PRT (PCI Routing Table):
      "0-INTA, 1-INTB, 2-INTC, 3-INTD"

  Device-tree bindings are shifted by 1:
      "INTA=1, INTB=2, INTC=3, INTD=4"
  */
  UINT8                               PciInterrupt;

  /** Interrupt controller interrupt.

  Cf Devicetree Specification - Release v0.3
  s2.4.3 "Interrupt Nexus Properties": "parent interrupt specifier"
  */
  CM_ARCH_COMMON_GENERIC_INTERRUPT    IntcInterrupt;
} CM_ARCH_COMMON_PCI_INTERRUPT_MAP_INFO;

/** A structure that describes the Memory Affinity Structure (Type 1) in SRAT

    ID: EArchCommonObjMemoryAffinityInfo
*/
typedef struct CmArchCommonMemoryAffinityInfo {
  /// The proximity domain to which the "range of memory" belongs.
  UINT32    ProximityDomain;

  /// Base Address
  UINT64    BaseAddress;

  /// Length
  UINT64    Length;

  /// Flags
  UINT32    Flags;
} CM_ARCH_COMMON_MEMORY_AFFINITY_INFO;

/** A structure that describes the ACPI Device Handle (Type 0) in the
    Generic Initiator Affinity structure in SRAT

    ID: EArchCommonObjDeviceHandleAcpi
*/
typedef struct CmArchCommonDeviceHandleAcpi {
  /// Hardware ID
  UINT64    Hid;

  /// Unique Id
  UINT32    Uid;
} CM_ARCH_COMMON_DEVICE_HANDLE_ACPI;

/** A structure that describes the PCI Device Handle (Type 1) in the
    Generic Initiator Affinity structure in SRAT

    ID: EArchCommonObjDeviceHandlePci
*/
typedef struct CmArchCommonDeviceHandlePci {
  /// PCI Segment Number
  UINT16    SegmentNumber;

  /// PCI Bus Number - Max 256 busses (Bits 15:8 of BDF)
  UINT8     BusNumber;

  /// PCI Device Number - Max 32 devices (Bits 7:3 of BDF)
  UINT8     DeviceNumber;

  /// PCI Function Number - Max 8 functions (Bits 2:0 of BDF)
  UINT8     FunctionNumber;
} CM_ARCH_COMMON_DEVICE_HANDLE_PCI;

/** A structure that describes the Generic Initiator Affinity structure in SRAT

    ID: EArchCommonObjGenericInitiatorAffinityInfo
*/
typedef struct CmArchCommonGenericInitiatorAffinityInfo {
  /// The proximity domain to which the generic initiator belongs.
  UINT32             ProximityDomain;

  /// Flags
  UINT32             Flags;

  /// Device Handle Type
  UINT8              DeviceHandleType;

  /// Reference Token for the Device Handle
  CM_OBJECT_TOKEN    DeviceHandleToken;
} CM_ARCH_COMMON_GENERIC_INITIATOR_AFFINITY_INFO;

/** A structure that describes the Lpi information.

  The Low Power Idle states are described in DSDT/SSDT and associated
  to cpus/clusters in the cpu topology.

  ID: EArchCommonObjLpiInfo
*/
typedef struct CmArchCommonLpiInfo {
  /** Minimum Residency. Time in microseconds after which a
      state becomes more energy efficient than any shallower state.
  */
  UINT32                                    MinResidency;

  /** Worst case time in microseconds from a wake interrupt
      being asserted to the return to a running state
  */
  UINT32                                    WorstCaseWakeLatency;

  /** Flags.
  */
  UINT32                                    Flags;

  /** Architecture specific context loss flags.
  */
  UINT32                                    ArchFlags;

  /** Residency counter frequency in cycles-per-second (Hz).
  */
  UINT32                                    ResCntFreq;

  /** Every shallower power state in the parent is also enabled.
  */
  UINT32                                    EnableParentState;

  /** The EntryMethod _LPI field can be described as an integer
      or in a Register resource data descriptor.

  If IsInteger is TRUE, the IntegerEntryMethod field is used.
  If IsInteger is FALSE, the RegisterEntryMethod field is used.
  */
  BOOLEAN                                   IsInteger;

  /** EntryMethod described as an Integer.
  */
  UINT64                                    IntegerEntryMethod;

  /** EntryMethod described as a EFI_ACPI_GENERIC_REGISTER_DESCRIPTOR.
  */
  EFI_ACPI_6_3_GENERIC_ADDRESS_STRUCTURE    RegisterEntryMethod;

  /** Residency counter register.
  */
  EFI_ACPI_6_3_GENERIC_ADDRESS_STRUCTURE    ResidencyCounterRegister;

  /** Usage counter register.
  */
  EFI_ACPI_6_3_GENERIC_ADDRESS_STRUCTURE    UsageCounterRegister;

  /** String representing the Lpi state
  */
  CHAR8                                     StateName[16];
} CM_ARCH_COMMON_LPI_INFO;

/** A structure that describes the Processor Hierarchy Node (Type 0) in PPTT

    ID: EArchCommonObjProcHierarchyInfo
*/
typedef struct CmArchCommonProcHierarchyInfo {
  /// A unique token used to identify this object
  CM_OBJECT_TOKEN    Token;
  /// Processor structure flags (ACPI 6.3 - January 2019, PPTT, Table 5-155)
  UINT32             Flags;
  /// Token for the parent CM_ARCH_COMMON_PROC_HIERARCHY_INFO object in the processor
  /// topology. A value of CM_NULL_TOKEN means this node has no parent.
  CM_OBJECT_TOKEN    ParentToken;
  /// Token of the associated object which has the corresponding ACPI Processor
  /// ID, e.g. for Arm systems this is a reference to CM_ARM_GICC_INFO object.
  /// A value of CM_NULL_TOKEN means this node represents a group of associated
  /// processors and it does not have an associated CPU interface.
  CM_OBJECT_TOKEN    AcpiIdObjectToken;
  /// Number of resources private to this Node
  UINT32             NoOfPrivateResources;
  /// Token of the array which contains references to the resources private to
  /// this CM_ARCH_COMMON_PROC_HIERARCHY_INFO instance. This field is ignored if
  /// the NoOfPrivateResources is 0, in which case it is recommended to set
  /// this field to CM_NULL_TOKEN.
  CM_OBJECT_TOKEN    PrivateResourcesArrayToken;
  /// Optional field: Reference Token for the Lpi state of this processor.
  /// Token identifying a CM_ARCH_COMMON_OBJ_REF structure, itself referencing
  /// CM_ARCH_COMMON_LPI_INFO objects.
  CM_OBJECT_TOKEN    LpiToken;
  /// Set to TRUE if UID should override index for name and _UID
  /// for processor container nodes and name of processors.
  /// This should be consistently set for containers or processors to avoid
  /// duplicate values
  BOOLEAN            OverrideNameUidEnabled;
  /// If OverrideNameUidEnabled is TRUE then this value will be used for name of
  /// processors and processor containers.
  UINT16             OverrideName;
  /// If OverrideNameUidEnabled is TRUE then this value will be used for
  /// the UID of processor containers.
  UINT32             OverrideUid;
} CM_ARCH_COMMON_PROC_HIERARCHY_INFO;

/** A structure that describes the Cache Type Structure (Type 1) in PPTT

    ID: EArchCommonObjCacheInfo
*/
typedef struct CmArchCommonCacheInfo {
  /// A unique token used to identify this object
  CM_OBJECT_TOKEN    Token;
  /// Reference token for the next level of cache that is private to the same
  /// CM_ARCH_COMMON_PROC_HIERARCHY_INFO instance. A value of CM_NULL_TOKEN
  /// means this entry represents the last cache level appropriate to the
  ///  processor hierarchy node structures using this entry.
  CM_OBJECT_TOKEN    NextLevelOfCacheToken;
  /// Size of the cache in bytes
  UINT32             Size;
  /// Number of sets in the cache
  UINT32             NumberOfSets;
  /// Integer number of ways. The maximum associativity supported by
  /// ACPI Cache type structure is limited to MAX_UINT8. However,
  /// the maximum number of ways supported by the architecture is
  /// PPTT_ARM_CCIDX_CACHE_ASSOCIATIVITY_MAX. Therfore this field
  /// is 32-bit wide.
  UINT32             Associativity;
  /// Cache attributes (ACPI 6.4 - January 2021, PPTT, Table 5.140)
  UINT8              Attributes;
  /// Line size in bytes
  UINT16             LineSize;
  /// Unique ID for the cache
  UINT32             CacheId;
} CM_ARCH_COMMON_CACHE_INFO;

/** A structure that describes the Cpc information.

  Continuous Performance Control is described in DSDT/SSDT and associated
  to cpus/clusters in the cpu topology.

  Unsupported Optional registers should be encoded with NULL resource
  Register {(SystemMemory, 0, 0, 0, 0)}

  For values that support Integer or Buffer, integer will be used
  if buffer is NULL resource.
  If resource is not NULL then Integer must be 0

  Cf. ACPI 6.4, s8.4.7.1 _CPC (Continuous Performance Control)

  ID: EArchCommonObjCpcInfo
*/
typedef AML_CPC_INFO CM_ARCH_COMMON_CPC_INFO;

/** A structure that describes a
    PCC Mailbox Register.
*/
typedef struct PccMailboxRegisterInfo {
  /// GAS describing the Register.
  EFI_ACPI_6_4_GENERIC_ADDRESS_STRUCTURE    Register;

  /** Mask of bits to preserve when writing.

    This mask is also used for registers. The Register is only read
    and there is no write mask required. E.g.:
    - Error Status mask (Cf. PCC Subspace types 3/4/5).
    - Command Complete Check mask (Cf. PCC Subspace types 3/4/5).
  */
  UINT64    PreserveMask;

  /// Mask of bits to set when writing.
  UINT64    WriteMask;
} PCC_MAILBOX_REGISTER_INFO;

/** A structure that describes the
    PCC Subspace CHannel Timings.
*/
typedef struct PccSubspaceChannelTimingInfo {
  /// Expected latency to process a command, in microseconds.
  UINT32    NominalLatency;

  /** Maximum number of periodic requests that the subspace channel can
      support, reported in commands per minute. 0 indicates no limitation.

    This field is ignored for the PCC Subspace type 5 (HW Registers based).
  */
  UINT32    MaxPeriodicAccessRate;

  /** Minimum amount of time that OSPM must wait after the completion
      of a command before issuing the next command, in microseconds.
  */
  UINT16    MinRequestTurnaroundTime;
} PCC_SUBSPACE_CHANNEL_TIMING_INFO;

/** A structure that describes a
    Generic PCC Subspace (Type 0).
*/
typedef struct PccSubspaceGenericInfo {
  /** Subspace Id.

  Cf. ACPI 6.4, s14.7 Referencing the PCC address space
  Cf. s14.1.2 Platform Communications Channel Subspace Structures
      The subspace ID of a PCC subspace is its index in the array of
      subspace structures, starting with subspace 0.

  At most 256 subspaces are supported.
  */
  UINT8                               SubspaceId;

  /// Table type (or subspace).
  UINT8                               Type;

  /// Base address of the shared memory range.
  /// This field is ignored for the PCC Subspace type 5 (HW Registers based).
  UINT64                              BaseAddress;

  /// Address length.
  UINT64                              AddressLength;

  /// Doorbell Register.
  PCC_MAILBOX_REGISTER_INFO           DoorbellReg;

  /// Mailbox Timings.
  PCC_SUBSPACE_CHANNEL_TIMING_INFO    ChannelTiming;
} PCC_SUBSPACE_GENERIC_INFO;

/** A structure that describes a
    PCC Subspace of type 0 (Generic).

    ID: EArchCommonObjPccSubspaceType0Info
*/
typedef PCC_SUBSPACE_GENERIC_INFO CM_ARCH_COMMON_PCC_SUBSPACE_TYPE0_INFO;

/** A structure that describes a
    PCC Subspace of type 1 (HW-Reduced).

    ID: EArchCommonObjPccSubspaceType1Info
*/
typedef struct CmArchCommonPccSubspaceType1Info {
  /** Generic Pcc information.

    The Subspace of Type0 contains information that can be re-used
    in other Subspace types.
  */
  PCC_SUBSPACE_GENERIC_INFO           GenericPccInfo;

  /// Platform Interrupt.
  CM_ARCH_COMMON_GENERIC_INTERRUPT    PlatIrq;
} CM_ARCH_COMMON_PCC_SUBSPACE_TYPE1_INFO;

/** A structure that describes a
    PCC Subspace of type 2 (HW-Reduced).

    ID: EArchCommonObjPccSubspaceType2Info
*/
typedef struct CmArchCommonPccSubspaceType2Info {
  /** Generic Pcc information.

    The Subspace of Type0 contains information that can be re-used
    in other Subspace types.
  */
  PCC_SUBSPACE_GENERIC_INFO           GenericPccInfo;

  /// Platform Interrupt.
  CM_ARCH_COMMON_GENERIC_INTERRUPT    PlatIrq;

  /// Platform Interrupt Register.
  PCC_MAILBOX_REGISTER_INFO           PlatIrqAckReg;
} CM_ARCH_COMMON_PCC_SUBSPACE_TYPE2_INFO;

/** A structure that describes a
    PCC Subspace of type 3 (Extended)

    ID: EArchCommonObjPccSubspaceType3Info
*/
typedef struct CmArchCommonPccSubspaceType3Info {
  /** Generic Pcc information.

    The Subspace of Type0 contains information that can be re-used
    in other Subspace types.
  */
  PCC_SUBSPACE_GENERIC_INFO           GenericPccInfo;

  /// Platform Interrupt.
  CM_ARCH_COMMON_GENERIC_INTERRUPT    PlatIrq;

  /// Platform Interrupt Register.
  PCC_MAILBOX_REGISTER_INFO           PlatIrqAckReg;

  /// Command Complete Check Register.
  /// The WriteMask field is not used.
  PCC_MAILBOX_REGISTER_INFO           CmdCompleteCheckReg;

  /// Command Complete Update Register.
  PCC_MAILBOX_REGISTER_INFO           CmdCompleteUpdateReg;

  /// Error Status Register.
  /// The WriteMask field is not used.
  PCC_MAILBOX_REGISTER_INFO           ErrorStatusReg;
} CM_ARCH_COMMON_PCC_SUBSPACE_TYPE3_INFO;

/** A structure that describes a
    PCC Subspace of type 4 (Extended)

    ID: EArchCommonObjPccSubspaceType4Info
*/
typedef CM_ARCH_COMMON_PCC_SUBSPACE_TYPE3_INFO CM_ARCH_COMMON_PCC_SUBSPACE_TYPE4_INFO;

/** A structure that describes a
    PCC Subspace of type 5 (HW-Registers).

    ID: EArchCommonObjPccSubspaceType5Info
*/
typedef struct CmArchCommonPccSubspaceType5Info {
  /** Generic Pcc information.

    The Subspace of Type0 contains information that can be re-used
    in other Subspace types.

    MaximumPeriodicAccessRate doesn't need to be populated for
    this structure.
  */
  PCC_SUBSPACE_GENERIC_INFO           GenericPccInfo;

  /// Version.
  UINT16                              Version;

  /// Platform Interrupt.
  CM_ARCH_COMMON_GENERIC_INTERRUPT    PlatIrq;

  /// Command Complete Check Register.
  /// The WriteMask field is not used.
  PCC_MAILBOX_REGISTER_INFO           CmdCompleteCheckReg;

  /// Error Status Register.
  /// The WriteMask field is not used.
  PCC_MAILBOX_REGISTER_INFO           ErrorStatusReg;
} CM_ARCH_COMMON_PCC_SUBSPACE_TYPE5_INFO;

/** A structure that describes a
    P-State Dependency (PSD) Info.

    Cf. ACPI 6.5, s8.4.5.5 _PSD (P-State Dependency).

    ID: EArchCommonObjPsdInfo
*/
typedef AML_PSD_INFO CM_ARCH_COMMON_PSD_INFO;

#pragma pack()

#endif // ARCH_COMMON_NAMESPACE_OBJECTS_H_
