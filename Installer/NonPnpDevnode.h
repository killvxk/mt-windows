#pragma once
#include <memory>

class SystemInfoClass;

class NonPnpDevnode:
	public SP_DEVINFO_DATA
{
public:
	NonPnpDevnode(void);
	NonPnpDevnode(std::shared_ptr<SystemInfoClass> hInfo);
  NonPnpDevnode(std::shared_ptr<SystemInfoClass> hInfo, const SP_DEVINFO_DATA& data);
	~NonPnpDevnode(void);

private:
	std::shared_ptr<SystemInfoClass> m_hInfo;
	bool released;

  // The driver that will be installed, valid after Associate is called
	SP_DRVINFO_DATA m_driverInfo;

public:
  // Accessor methods:
  SP_DRVINFO_DATA& GetDriverInfo(void) {return m_driverInfo;}

	/// <summary>
	/// Attempts to associate this non-PNP DevNode with the HidEmulator device driver
	/// </summary>
	void Associate(void);

  /// <summary>
  /// Attempts to update the driver associated with this devnode
  /// </remarks>
  /// <returns>True if a reboot is required</returns>
  bool InstallDriver(void);

  void operator=(NonPnpDevnode&& rhs) {
    *(PSP_DEVINFO_DATA)this = rhs;
    m_hInfo = rhs.m_hInfo;
    released = rhs.released;
    rhs.released = true;
  }
};

