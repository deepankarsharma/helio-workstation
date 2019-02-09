/*
    This file is part of Helio Workstation.

    Helio is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Helio is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helio. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "BackendRequest.h"
#include "BaseResource.h"

class ConfigurationSyncThread final : public Thread, public WaitableEvent
{
public:

    ConfigurationSyncThread();
    ~ConfigurationSyncThread() override;

    Function<void()> onQueueEmptied;
    Function<void(const BaseResource::Ptr resource)> onResourceDeleted;
    Function<void(const BaseResource::Ptr resource)> onResourceUpdated;

    void queueConfigurationUpload(ReferenceCountedArray<BaseResource> resources);
    void queueConfigurationDelete(ReferenceCountedArray<BaseResource> resources);

private:

    void run() override;

    // If empty, synchronizes all revisions
    ReferenceCountedArray<BaseResource, CriticalSection> resourcesToUpload;
    ReferenceCountedArray<BaseResource, CriticalSection> resourcesToDelete;

    BackendRequest::Response response;

    friend class BackendService;
};