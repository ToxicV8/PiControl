/*Standard Library Includes*/
#include <string.h>
#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <thread>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <readline/readline.h>
#include <readline/history.h>
#include <chrono>

/*Custom Includes*/
#include "jsoncons/json.hpp"
#include "Structs.h"
#include "Logger.h"
#include "Typedefs.h"
#include "Helpers.h"
#include "Command.h"
#include "CommandSystem.h"
#include "GPIOControl.h"
#include "Variables.h"
#include "JsonObject.h"
#include "JsonCommands.h"
#include "JsonConfig.h"
#include "CallbackCommands.h"
#include "ThreadManager.h"
#include "Starter.h"


