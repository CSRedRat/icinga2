/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#include "base/fifo.h"
#include "base/utility.h"

using namespace icinga;

/**
 * Constructor for the FIFO class.
 */
FIFO::FIFO(void)
	: m_Buffer(NULL), m_DataSize(0), m_AllocSize(0), m_Offset(0)
{ }

/**
 * Destructor for the FIFO class.
 */
FIFO::~FIFO(void)
{
	free(m_Buffer);
}

/**
 * Resizes the FIFO's buffer so that it is at least newSize bytes long.
 *
 * @param newSize The minimum new size of the FIFO buffer.
 */
void FIFO::ResizeBuffer(size_t newSize)
{
	if (m_AllocSize >= newSize)
		return;

	newSize = (newSize / FIFO::BlockSize + 1) * FIFO::BlockSize;

	char *newBuffer = static_cast<char *>(realloc(m_Buffer, newSize));

	if (newBuffer == NULL)
		BOOST_THROW_EXCEPTION(std::bad_alloc());

	m_Buffer = newBuffer;

	m_AllocSize = newSize;
}

/**
 * Optimizes memory usage of the FIFO buffer by reallocating
 * and moving the buffer.
 */
void FIFO::Optimize(void)
{
	//char *newBuffer;

	if (m_DataSize < m_Offset) {
		memcpy(m_Buffer, m_Buffer + m_Offset, m_DataSize);
		m_Offset = 0;

		return;
	}

	/*newBuffer = (char *)ResizeBuffer(NULL, 0, m_BufferSize - m_Offset);

	if (newBuffer == NULL)
		return;

	memcpy(newBuffer, m_Buffer + m_Offset, m_BufferSize - m_Offset);

	free(m_Buffer);
	m_Buffer = newBuffer;
	m_BufferSize -= m_Offset;
	m_Offset = 0;*/
}

/**
 * Implements IOQueue::Read.
 */
size_t FIFO::Read(void *buffer, size_t count)
{
	if (count > m_DataSize)
		count = m_DataSize;

	if (buffer != NULL)
		memcpy(buffer, m_Buffer + m_Offset, count);

	m_DataSize -= count;
	m_Offset += count;

	Optimize();

	return count;
}

/**
 * Implements IOQueue::Write.
 */
void FIFO::Write(const void *buffer, size_t count)
{
	ResizeBuffer(m_Offset + m_DataSize + count);
	memcpy(m_Buffer + m_Offset + m_DataSize, buffer, count);
	m_DataSize += count;
}

void FIFO::Close(void)
{ }

size_t FIFO::GetAvailableBytes(void) const
{
	return m_DataSize;
}
