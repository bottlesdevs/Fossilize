/* Copyright (c) 2018 Hans-Kristian Arntzen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "device.hpp"
#include "instance.hpp"
#include "path.hpp"
#include "utils.hpp"
#include <cinttypes>
#include <stdlib.h>

namespace Fossilize
{

void Device::init(VkPhysicalDevice gpu_, VkDevice device_, Instance *pInstance_,
                  const void *device_pnext,
                  VkLayerDispatchTable *pTable_)
{
	gpu = gpu_;
	device = device_;
	pInstance = pInstance_;
	pInstanceTable = pInstance->getTable();
	pTable = pTable_;

	// For now, we're only sensitive to vendorID.
	VkPhysicalDeviceProperties2 props2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
	pInstanceTable->GetPhysicalDeviceProperties(gpu, &props2.properties);

	recorder = pInstance->getStateRecorderForDevice(&props2, pInstance->getApplicationInfo(), device_pnext);
}
}
