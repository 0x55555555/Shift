#include "shifttest.h"
#include "shift/Properties/sdata.inl"
#include "shift/Properties/scontaineriterators.h"

#include "shift/Serialisation/sjsonio.h"
#include "shift/Serialisation/sxmlio.h"

void buildTestData(Shift::Database* db)
  {
  auto ent = db->addChild<TestEntity>();

  auto indexed = ent->addChild<TestIndexedEntity>();

  auto vec1 = ent->addAttribute<TestVector>();
  auto vec2 = ent->addAttribute<TestVector>();

  auto vec3 = indexed->testArray.add<TestVector>();
  auto vec4 = indexed->testArray.add<TestVector>();

  vec1->x = 1.0f;
  vec1->y = 2.0f;
  vec1->z = 3.0f;

  vec3->setInput(vec1);
  vec2->setInput(vec3);

  vec4->x = 4.0f;
  vec4->y = 5.0f;
  vec4->z = 6.2f;
  }

void ShiftCoreTest::serialisationJsonTest()
  {
  TestDatabase db;

  buildTestData(&db);

  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);

  Shift::SaveVisitor visitor;

  Shift::JSONSaver writer;
  writer.setAutoWhitespace(true);

  QBENCHMARK {
    auto block = writer.beginWriting(&buffer);

    visitor.visit(&db, false, &writer);
  }

  //qDebug() << buffer.buffer();
  }
