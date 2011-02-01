// Acoustid Index -- Inverted index for audio fingerprints
// Copyright (C) 2011  Lukas Lalinsky
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ACOUSTID_FS_OUTPUT_STREAM_H_
#define ACOUSTID_FS_OUTPUT_STREAM_H_

#include <QString>
#include "buffered_output_stream.h"

class FSOutputStream : public BufferedOutputStream
{
public:
	explicit FSOutputStream(int fd);
	~FSOutputStream();

	int fileDescriptor() const;

	static FSOutputStream *open(const QString &fileName);

protected:
	size_t write(uint8_t *data, size_t offset, size_t length);

private:
	int m_fd;	
};

class NamedFSOutputStream : public FSOutputStream
{
public:
	NamedFSOutputStream(const QString &name, int fd);

	QString fileName() const;

	static NamedFSOutputStream *openTemporary();

private:
	QString m_fileName;
};

#endif
