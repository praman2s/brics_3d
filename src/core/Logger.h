// BRICS_3D - 3D Perception and Modeling Library
// Copyright (c) 2010 GPS GmbH
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iosfwd>
#include <sstream>
#include <string>

namespace BRICS_3D {

//! Various defines for logging
#define LOG(level) LOG_BRICS_ ## level
#define LOG_BRICS_DEBUG Logger(Logger::LOGDEBUG).write(__FILE__, __LINE__)
#define LOG_BRICS_INFO Logger(Logger::INFO).write(__FILE__, __LINE__)
#define LOG_BRICS_WARNING Logger(Logger::WARNING).write(__FILE__, __LINE__)
#define LOG_BRICS_ERROR Logger(Logger::LOGERROR).write(__FILE__, __LINE__)
#define LOG_BRICS_FATAL Logger(Logger::FATAL).write(__FILE__, __LINE__)

//! A logging service based on streams.
//!
//! Any class may use LOG() macros to send log output to a
//! predefined source, usually console or a file. Usage is as follows:
//! 
//! LOG(INFO) << "some text";
//!
//! The possible log levels are: INFO, WARNING, ERROR and FATAL.
//! One of those levels must always be provided. 
//! FATAL will exit the whole application.
//! The logging here is inspired by the Google Logging Library "glog", 
//! but in a very simplified form.
//!
//! The Logger class works by creating a new Logger object every time when
//! LOG() is called. When the object is deleted, the actual writing takes place.

class Logger {
public:
	//! Enum for possible log levels. Order is important here
	enum Loglevel {
		LOGDEBUG = 0,
		INFO = 1,
		WARNING = 2,
		LOGERROR = 3, // because windows redefines ERROR
		FATAL = 4
	};

	//! Simple observer class to handle log messages in custom way
	class Listener {
	public:
		virtual void write(Loglevel level, std::string message) = 0;
	};

	//! Constructor. Logger will only log if level if >= minLoglevel
	Logger(Loglevel level);

	//! Destructor. Calls flush() if required.
	virtual ~Logger();
	
	//! Sets minimum log level. Below \a minLoglevel, nothing will be logged.
	static void setMinLoglevel(Loglevel minLoglevel);

	//! Returns ths minimum log level. Below \a minLoglevel, nothing is logged.
	static Loglevel getMinLoglevel();

	//! Writes log output to the file with given \a filename.
	static void setLogfile(std::string filename, bool append = false);

	//! Sets wether log messages shall include the filename and line of where LOG() was called
	static void setUseFilename(bool useFilename);

	//! Sets a new listener for log messages. To remove the listener (maybe because it has been destructed) pass the NULL reference.
	static void setListener(Listener* listener);

	//! Initiates writing log output. The actual writing occurs
	//! when the Logger object is deleted.
	std::ostream& write(std::string filename, int line);

protected:
	//! Writes the logging text to its destination.
	void flush();

	//! Converts \a loglevel into a string.
	std::string& levelToString(Loglevel loglevel);

	static Loglevel minLoglevel;
	static bool useFilename;
	static bool useLogfile;
	static std::string logfilename;
	static std::ofstream logfile;
	static Listener* listener;
	
	std::ostringstream stream;
	Loglevel level;
	bool isAboveLoglevel;
	bool needNewline;

};

} //namespace BRICS_3D

#endif // LOGGER_H_

