#include "../config.h"

#include <string>
#include <thread>
#include <future>
#include <iostream>
#include <stdio.h>
#include <map>

#include <spdlog\spdlog.h>

#include "data/server_data.h"
#include "data/flag_data.h"
#include "data/ruc_data.h"
#include "data/file_data.h"

#include "tool/http.h"
#include "tool/zip.h"
#include "tool/algorithms.h"

#include "dao/mysql.h"
#include "dao/empresa_dao.h"

#include "gui/i_gui.h"
#include "gui/insert_gui.h"
#include "gui/update_gui.h"
#include "gui/query_gui.h"

#include "system/app.h"
#include "system/console.h"