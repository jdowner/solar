#include <stdexcept>
#include <iostream>

#include "Engine.h"
#include "DataStore.h"
#include "ArgumentHandler.h"

int main(int argc, char** argv)
{
  try
  {
    ArgumentHandler arguments(argc, argv);
    DataStore datastore;

    if (arguments.configuration())
    {
      datastore.load(arguments.getConfiguration());
    }
    else
    {
      datastore.load(arguments.getResourcePath() + "default.yaml");
    }

//    DataStore::set("debug", arguments.debug());
//    DataStore::set("resource-path", arguments.getResourcePath());

    Engine engine(datastore);

    engine.init();

    while (engine.running())
    {
      engine.update();
      engine.render();
      engine.sleep();
    }

    engine.shutdown();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Encountered unrecognized exception" << std::endl;
  }

  return 0;
}
