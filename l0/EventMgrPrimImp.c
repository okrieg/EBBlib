/*
 * Copyright (C) 2011 by Project SESA, Boston University
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <config.h>
#include <stdint.h>
#include <inttypes.h>

#include <l0/lrt/types.h>
#include <l0/cobj/cobj.h>
#include <lrt/io.h>
#include <l0/lrt/trans.h>
#include <l0/types.h>
#include <l0/sys/trans.h>
#include <lrt/assert.h>
#include <l0/cobj/CObjEBB.h>
#include <l0/EBBMgrPrim.h>
#include <l0/cobj/CObjEBBUtils.h>
#include <l0/cobj/CObjEBBRoot.h>
#include <l0/cobj/CObjEBBRootMulti.h>
#include <l0/cobj/CObjEBBRootMultiImp.h>
#include <l0/EventMgrPrim.h>
#include <l0/EventMgrPrimImp.h>
#include <l0/MemMgr.h>
#include <l0/MemMgrPrim.h>
#include <l0/lrt/event.h>

STATIC_ASSERT(LRT_EVENT_NUM_EVENTS % 8 == 0,
	      "num allocatable events isn't divisible by 8");
static uint8_t alloc_table[LRT_EVENT_NUM_ALLOCATABLE_EVENTS / 8];

CObject(EventMgrPrimImp){
  CObjInterface(EventMgrPrim) *ft;
};

EventMgrPrimId theEventMgrPrimId=0;

static EBBRC 
EventMgrPrim_allocEventNo(EventMgrPrimRef _self, EventNo *eventNoPtr)
{
  int i;
  //we start from the beginning and just find the first
  // unallocated event
  for (i = 0; i < LRT_EVENT_NUM_ALLOCATABLE_EVENTS; i++) {
    uint8_t res = __sync_fetch_and_or(&alloc_table[i / 8], 1 << (i % 8));
    if (!(res & (1 << (i % 8)))) {
      break;
    }
  }
  if (i >= LRT_EVENT_NUM_ALLOCATABLE_EVENTS) {
    return EBBRC_OUTOFRESOURCES;
  }
  *eventNoPtr = i + LRT_EVENT_FIRST_ALLOCATABLE_EVENT;
  return EBBRC_OK;
}

EBBRC 
EventMgrPrim_freeEventNo(EventMgrPrimRef _self, EventNo eventNo)
{
  eventNo -= LRT_EVENT_FIRST_ALLOCATABLE_EVENT;
  __sync_fetch_and_and(&alloc_table[eventNo / 8], ~(1 << (eventNo % 8)));
  return EBBRC_OK;
}

EBBRC 
EventMgrPrim_bindEvent(EventMgrPrimRef _self, EventNo eventNo,
	  EBBId handler, FuncNum fn)
{
  LRT_Assert(0);
}

EBBRC 
EventMgrPrim_routeIRQ(EventMgrPrimRef _self, IRQ *isrc, EventNo eventNo,
		      EventLoc el)
{
  LRT_Assert(0);
}

EBBRC 
EventMgrPrim_triggerEvent(EventMgrPrimRef _self, EventNo eventNo, EventLoc el)
{
  LRT_Assert(0);
}

CObjInterface(EventMgrPrim) EventMgrPrimImp_ftable = {
  .allocEventNo = EventMgrPrim_allocEventNo, 
  .freeEventNo = EventMgrPrim_freeEventNo, 
  .bindEvent = EventMgrPrim_bindEvent, 
  .routeIRQ = EventMgrPrim_routeIRQ, 
  .triggerEvent = EventMgrPrim_triggerEvent 
};

static void
EventMgrPrimSetFT(EventMgrPrimImpRef o)
{
  o->ft = &EventMgrPrimImp_ftable;
}

static EBBRep *
EventMgrPrimImp_createRepAssert(CObjEBBRootMultiRef root) 
{
  LRT_Assert(0);
  return NULL;
}

static EventMgrPrimImpRef
EventMgrPrimImp_createRep(CObjEBBRootMultiImpRef root) 
{
  EventMgrPrimImpRef repRef;

  LRT_RCAssert(EBBPrimMalloc(sizeof(EventMgrPrimImp), &repRef, EBB_MEM_DEFAULT));
  EventMgrPrimSetFT(repRef);
  return repRef;
}

EBBRC
EventMgrPrimImpInit(void)
{
  EBBRC rc;
  static CObjEBBRootMultiImpRef rootRef;
  EventMgrPrimImpRef repRef;
  EventLoc myel;

  if (__sync_bool_compare_and_swap(&theEventMgrPrimId, (EventMgrPrimId)0,
				   (EventMgrPrimId)-1)) {
    EBBId id;
     rc = CObjEBBRootMultiImpCreate(&rootRef, EventMgrPrimImp_createRepAssert);
    LRT_RCAssert(rc);
    rc = EBBAllocPrimId(&id);
    LRT_RCAssert(rc);
    rc = EBBBindPrimId(id, CObjEBBMissFunc, (EBBMissArg)rootRef);
    LRT_RCAssert(rc);
    theEventMgrPrimId = (EventMgrPrimId)id;
  } else {
    while (((volatile uintptr_t)theEventMgrPrimId)==-1);
  }
  // It makes no sense to handle miss on this object lazily, since it will 
  // always be invoked on every node, everything is in an event
  repRef = EventMgrPrimImp_createRep(rootRef);
  myel = MyEventLoc();
  
  rootRef->ft->addRepOn((CObjEBBRootMultiRef)rootRef, myel, (EBBRep *)repRef);
  return EBBRC_OK;
};

