#include "Device.h"

void Device::generateId()
{
  static int nid = 0;
  nid++;
  std::stringstream ss;
  ss << this->type << nid;
  this->id = ss.str();
}

std::string Device::getId()
{
  return id;
}

std::string Device::getStatus()
{
  return this->state.getDescription();
}

std::string Device::getDeviceType()
{
  return this->type;
}

void Device::notify()
{
  throw "Device notify() Not implemented";
}

void Device::setState(DeviceState newState)
{
  state = newState;
}