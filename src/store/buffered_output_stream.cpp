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

#include "buffered_output_stream.h"

BufferedOutputStream::BufferedOutputStream(size_t bufferSize)
	: m_bufferSize(bufferSize), m_start(0), m_position(0)
{
	m_buffer = new uint8_t[m_bufferSize];
}

BufferedOutputStream::~BufferedOutputStream()
{
	if (m_buffer) {
		delete[] m_buffer;
	}
}

size_t BufferedOutputStream::bufferSize()
{
	return m_bufferSize;
}

void BufferedOutputStream::setBufferSize(size_t bufferSize)
{
	flushBuffer();
	m_bufferSize = bufferSize;
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer = new uint8_t[m_bufferSize];
	}
}

void BufferedOutputStream::writeByte(uint8_t b)
{
	if (m_position >= m_bufferSize) {
		flushBuffer();
	}
	m_buffer[m_position++] = b;
}

void BufferedOutputStream::flushBuffer()
{
	if (m_position) {
		write(m_buffer, m_start, m_position);
		m_start += m_position;
		m_position = 0;
	}
}

void BufferedOutputStream::flush()
{
	flushBuffer();
}

size_t BufferedOutputStream::position()
{
	return m_start + m_position;
}

void BufferedOutputStream::seek(size_t position)
{
	flushBuffer();
	m_start = position;
}
