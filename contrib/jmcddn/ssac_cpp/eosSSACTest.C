#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "EBBKludge.H"

#include "Test.H"

#include "SSACSimpleSharedArray.H"

class MySSAC : public SSAC {
public:
  virtual EBBRC get( CacheObjectId &id, CacheEntry* &ce,
		     const gettype &type );
  virtual EBBRC putback( CacheEntry* &ce, const putflag &flag );
  virtual EBBRC flush();
  virtual EBBRC snapshot();
  static  EBBRC create(MySSAC **o);
};

/* statick */ EBBRC
MySSAC::create(MySSAC **o)
{
  *o = new(MySSAC);
  return 0;
}

/* virtual */ EBBRC
MySSAC::get( CacheObjectId &id, CacheEntry* &ce,
	     const gettype &type )
{
  return (EBBRC)0;
}

/* virtual */ EBBRC
MySSAC::putback( CacheEntry* &ce, const putflag &flag )
{
  return (EBBRC)0;
}

/* virtual */ EBBRC
MySSAC::flush()
{
  TRACE("BEGIN");
  return (EBBRC)0;
}

/* virtual */ EBBRC
MySSAC::snapshot()
{
  return (EBBRC)0;
}


#if 0
class BTest : public Test {
  Barrier b;
protected:
  EBBRC work(int id);
  EBBRC init() {return 0;};
public:
  BTest(int n) : Test(n), b(n) {}; // TODO: what with the syntax
};

EBBRC
BTest::work(int id)
{
  TRACE("%d: BEGIN: %p", id, this);
  for (int j=0; j<2; j++) {
    if (id != (numWorkers - 1) ) {
      TRACE("%d: Not last worker entering Barrier %p\n", id, &b);
      b.enter();
      TRACE("%d: Not last worker LEFT Barrier %p\n", id, &b);
    } else {
      TRACE("%d: LAST worker Sleeping %p\n", id, &b);
      for (volatile int i=0; i<1000000000; i++);
      TRACE("%d: Last worker entering Barrier %p\n", id, &b);
      b.enter();
      TRACE("%d: Last worker LEFT Barrier %p\n", id, &b);
    }
    TRACE("%d: Worker doing test AGAIN %p\n", id, &b);
  }
  TRACE("%d: END: %p", id, this);
  return 0;
}

void
BarrierTest(int numWorkers)
{
  TRACE("BEGIN: %d\n", numWorkers);

  BTest b(numWorkers);

  b.doTest();

  TRACE("END\n");
}
#endif

class SSACTest : public Test {
protected:
  SSACId ssac;
  enum {HASHTABLESIZE=8192};//this is the size of hashqs, each with an 'associative' ammount of entries.
  EBBRC work(int id);
  EBBRC init();
  EBBRC end();
public:
  SSACTest(int n, int m, int c, bool p, double wpct): Test(n,m,c,p,wpct) {}

};

/* Initialise array */
EBBRC
SSACTest::init()
{
//  TRACE("BEGIN");
  CacheObjectIdSimple id(0);
  CacheEntrySimple *entry=0;
  EBBRC rc;
  // run through each entry of the hashqs, clear value & h
  DREF(ssac)->flush();

  for (unsigned long i=0; i<HASHTABLESIZE; i++) {
    id = i;
    rc=DREF(ssac)->get((CacheObjectId &)id,(CacheEntry * &)entry,
		       SSAC::GETFORWRITE);
    entry->data = (void *)i; // set data pointer to i TODO: verify
    rc=DREF(ssac)->putback((CacheEntry * &)entry, SSAC::KEEP);
  }
//  TRACE("END");
  return rc;
}

/**
 * SSACTest:work() -- pull and update an entry from each hashq of the cache
 * */
EBBRC
SSACTest::work(int myid)
{
  //  TRACE("BEGIN");
  CacheObjectIdSimple id(0);
  CacheEntrySimple *entry=0;
  int readCount, writeCount;
  EBBRC rc;
  intptr_t v;

  readCount = (1-writePct) * numEvents;
  writeCount = writePct * numEvents;

  for (int j=0; j<1;j++) {
    // write to SSAC data object (increase pointer by 1)
    for (int i=0; i<writeCount; i++) {
      id = i;
      rc = DREF(ssac)->get((CacheObjectId &)id,(CacheEntry * &)entry,
			   SSAC::GETFORWRITE);
      v=(intptr_t)entry->data; v++; entry->data=(void *)v;
      entry->dirty();
      rc =DREF(ssac)->putback((CacheEntry * &)entry, SSAC::KEEP);
    }
    for (int k=0; k<readCount; k++){
      id = k;
      rc = DREF(ssac)->get((CacheObjectId &)id,(CacheEntry * &)entry,
			   SSAC::GETFORREAD);
      v=(intptr_t)entry->data;
    }
  }
  //  TRACE("END");
  return rc;
}

EBBRC
SSACTest::end()
{
 // TRACE("BEGIN");
 // DREF(ssac)->snapshot();
//  TRACE("Tests:end: \n");
  Test::end();
//  TRACE("END");
  return 0;
}

class SSATest : public SSACTest {
public:
  SSATest(int n, int m, int c, bool p, double wpct);
  virtual ~SSATest();
};

SSATest::SSATest(int n, int m, int c, bool p, double wpct) : SSACTest(n,m,c,p,wpct)
{
  // init hash table
  SSACSimpleSharedArray::Create(ssac, HASHTABLESIZE);
}

SSATest::~SSATest()
{
  // DREF(ssac)->destroy();
}

void
SSACSimpleSharedArrayTest(int numWorkers, int numIterations, int numEvents, bool bindThread, double wpct)
{
//  TRACE("BEGIN");
  SSATest test(numWorkers, numIterations, numEvents, bindThread, wpct);
  test.doTest();
//  TRACE("END");
}

int
main(int argc, char **argv)
{
  int n=4; // thread count
  int m=1; // no. of iterations
  bool p=1; // bind threads?
  double w=0.5; // test read/write percentage
  int c=1000; // test event no

  if (argc>1) n=atoi(argv[1]);
  if (argc>2) m=atoi(argv[2]);
  if (argc>3) c=atoi(argv[3]);
  if (argc>4) w=atof(argv[4]);
  if (argc>5) p=atoi(argv[5]);

#if 0
  BarrierTest(n);
#endif

  SSACSimpleSharedArrayTest(n,m,c,p,w);

  return 0;
}
