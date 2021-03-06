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

    datastore.set("window-height", 800.0);
    datastore.set("window-width", 1000.0);

    datastore.set("viewport-min-x", -300.0);
    datastore.set("viewport-min-y", -300.0);
    datastore.set("viewport-max-x", +300.0);
    datastore.set("viewport-max-y", +300.0);

    datastore.set("images-star", "/home/jdowner/repos/solar/build/share/solar/images/moon.png");

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
