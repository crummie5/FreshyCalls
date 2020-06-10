// Copyright (c) 2020 ElephantSe4l. All Rights Reserved.
// Released under MPL-2.0, see LICENCE for more information.

#ifndef FRESHYCALLS_NATIVE_HPP_
#define FRESHYCALLS_NATIVE_HPP_

#include <cstdint>

namespace freshycalls::native {
struct LinkedList {
  LinkedList *Flink;
  LinkedList *Blink;
};


struct UnicodeString {
  uint16_t Length;
  uint16_t MaximumLength;
  wchar_t *Buffer;
};


struct LdrDataEntry {
  LinkedList InLoadOrderLinks;
  LinkedList InMemoryOrderLinks;
  LinkedList InInitializationOrderLinks;
  void *DllBase;
  void *EntryPoint;
  uint32_t SizeOfImage;
  LinkedList FullDllName;
  LinkedList BaseDllName;
  uint32_t Flags;
  uint16_t LoadCount;
  uint16_t TlsIndex;
};


struct LdrData {
  uint32_t Length;
  uint8_t Initialized;
  void *SsHandle;
  LinkedList InLoadOrderModuleList;
  LinkedList InMemoryOrderModuleList;
  union {
    LinkedList InInitializationOrderModuleList;
    LinkedList InProgressLinks;
  };
  void *EntryInProgress;
};


struct PEB {
  bool InheritedAddressSpace;
  bool ReadImageFileExecOptions;
  bool BeingDebugged;
  bool ImageUsesLargePages: 1;
  bool IsProtectedProcess: 1;
  bool IsImageDynamicallyRelocated: 1;
  bool SkipPatchingUser32Forwarders: 1;
  bool IsPackagedProcess: 1;
  bool IsAppContainer: 1;
  bool IsProtectedProcessLight: 1;
  bool IsLongPathAwareProcess: 1;
  void *Mutant;
  void *ImageBaseAddress;
  LdrData *Ldr;
  void *ProcessParameters;
  void *SubSystemData;
  void *ProcessHeap;
  void *FastPebLock;
  void *AtlThunkSListPtr;
  void *IFEOKey;
  bool ProcessInJob: 1;
  bool ProcessInitializing: 1;
  bool ProcessUsingVEH: 1;
  bool ProcessUsingVCH: 1;
  bool ProcessUsingFTH: 1;
  bool ProcessPreviouslyThrottled: 1;
  bool ProcessCurrentlyThrottled: 1;
  bool ProcessImagesHotPatched: 1;
  uint32_t ReservedBits0: 24;
  union {
    void *KernelCallbackTable;
    void *UserSharedInfoPtr;
  };
  uint32_t SystemReserved;
  uint32_t AtlThunkSListPtr32;
  void *ApiSetMap;
  uint32_t TlsExpansionCounter;
  void *TlsBitmap;
  uint32_t TlsBitmapBits[2];
  void *ReadOnlySharedMemoryBase;
  void *HotpatchInformation;
  void **ReadOnlyStaticServerData;
  void *AnsiCodePageData;
  void *OemCodePageData;
  void *UnicodeCaseTableData;
  uint32_t NumberOfProcessors;
  uint32_t NtGlobalFlag;
  uint64_t CriticalSectionTimeout;
  size_t HeapSegmentReserve;
  size_t HeapSegmentCommit;
  size_t HeapDeCommitTotalFreeThreshold;
  size_t HeapDeCommitFreeBlockThreshold;
  uint32_t NumberOfHeaps;
  uint32_t MaximumNumberOfHeaps;
  void **ProcessHeaps;
  void *GdiSharedHandleTable;
  void *ProcessStarterHelper;
  uint32_t GdiDCAttributeList;
  void *LoaderLock;
  uint32_t OSMajorVersion;
  uint32_t OSMinorVersion;
  uint16_t OSBuildNumber;
  uint16_t OSCSDVersion;
  uint32_t OSPlatformId;
  uint32_t ImageSubsystem;
  uint32_t ImageSubsystemMajorVersion;
  uint32_t ImageSubsystemMinorVersion;
  uint32_t *ActiveProcessAffinityMask;
  uint32_t GdiHandleBuffer[60];
  void *PostProcessInitRoutine;
  void *TlsExpansionBitmap;
  uint32_t TlsExpansionBitmapBits[32];
  uint32_t SessionId;
};


struct DOSHeader {
  uint16_t e_magic;
  uint16_t e_cblp;
  uint16_t e_cp;
  uint16_t e_crlc;
  uint16_t e_cparhdr;
  uint16_t e_minalloc;
  uint16_t e_maxalloc;
  uint16_t e_ss;
  uint16_t e_sp;
  uint16_t e_csum;
  uint16_t e_ip;
  uint16_t e_cs;
  uint16_t e_lfarlc;
  uint16_t e_ovno;
  uint16_t e_res[4];
  uint16_t e_oemid;
  uint16_t e_oeminfo;
  uint16_t e_res2[10];
  int32_t e_lfanew;
};


struct FileHeader {
  uint16_t Machine;
  uint16_t NumberOfSections;
  uint32_t TimeDateStamp;
  uint32_t PointerToSymbolTable;
  uint32_t NumberOfSymbols;
  uint16_t SizeOfOptionalHeader;
  uint16_t Characteristics;
};


struct DataDirectory {
  uint32_t VirtualAddress;
  uint32_t Size;
};

enum DirectoryEntry : uint16_t {
  kExport,
  kImport,
  kResource,
  kException,
  kSecurity,
  kBaseReloc,
  kDebug,
  kArchitecture,
  kGlobalPtr,
  kTls,
  kBoundImport,
  kIAT,
  kDelayImport,
  kCOMDescriptor
};

struct OptionalHeader64 {
  uint16_t Magic;
  uint8_t MajorLinkerVersion;
  uint8_t MinorLinkerVersion;
  uint32_t SizeOfCode;
  uint32_t SizeOfInitializedData;
  uint32_t SizeOfUninitializedData;
  uint32_t AddressOfEntryPoint;
  uint32_t BaseOfCode;
  uint64_t ImageBase;
  uint32_t SectionAlignment;
  uint32_t FileAlignment;
  uint16_t MajorOperatingSystemVersion;
  uint16_t MinorOperatingSystemVersion;
  uint16_t MajorImageVersion;
  uint16_t MinorImageVersion;
  uint16_t MajorSubsystemVersion;
  uint16_t MinorSubsystemVersion;
  uint32_t Win32VersionValue;
  uint32_t SizeOfImage;
  uint32_t SizeOfHeaders;
  uint32_t CheckSum;
  uint16_t Subsystem;
  uint16_t DllCharacteristics;
  uint64_t SizeOfStackReserve;
  uint64_t SizeOfStackCommit;
  uint64_t SizeOfHeapReserve;
  uint64_t SizeOfHeapCommit;
  uint32_t LoaderFlags;
  uint32_t NumberOfRvaAndSizes;
  DataDirectory DataDirectory[16];
};


struct NTHeaders64 {
  uint32_t Signature;
  FileHeader FileHeader;
  OptionalHeader64 OptionalHeader;
};

struct ExportDirectory {
  uint32_t Characteristics;
  uint32_t TimeDateStamp;
  uint16_t MajorVersion;
  uint16_t MinorVersion;
  uint32_t Name;
  uint32_t Base;
  uint32_t NumberOfFunctions;
  uint32_t NumberOfNames;
  uint32_t AddressOfFunctions;
  uint32_t AddressOfNames;
  uint32_t AddressOfNameOrdinals;
};

}

#endif