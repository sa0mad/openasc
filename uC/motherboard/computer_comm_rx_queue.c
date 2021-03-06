/*! \file internal_comm_rx_queue.c
 *  \brief The internal communication RX QUEUE
 *  \ingroup internal_comm_group
 *  \author Mikael Larsmark, SM2WMV
 *  \date 2010-01-25
 *  \code #include "internal_comm_rx_queue.c" \endcode
 */
//    Copyright (C) 2008  Mikael Larsmark, SM2WMV
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

/* FIFO queue */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "computer_comm_rx_queue.h"

//! The RX queue
computer_comm_rx_queue_struct computer_comm_rx_queue;

/*! \brief Initialize the internal comm rx queue */
void computer_comm_rx_queue_init(void) {
	computer_comm_rx_queue.first = 0;
	computer_comm_rx_queue.last = 0;
  
  computer_comm_rx_queue.count = 0;
}

/*! \brief Insert a message into the TX queue (FIFO)
 * \param message - The message that should be inserted to the queue
 */
void computer_comm_rx_queue_add(COMM_MESSAGE message) {
	computer_comm_rx_queue.message[computer_comm_rx_queue.last++] = message;
	
	if (computer_comm_rx_queue.last >= COMPUTER_COMM_RX_QUEUE_SIZE)
		computer_comm_rx_queue.last = 0;
	
	if (computer_comm_rx_queue.last == computer_comm_rx_queue.first)
		computer_comm_rx_queue.first++;
	
	if (computer_comm_rx_queue.first >= COMPUTER_COMM_RX_QUEUE_SIZE)
		computer_comm_rx_queue.first = 0;	
  
  computer_comm_rx_queue.count++;
}

/*!\brief Retrieve the first message from the FIFO TX queue.
 * \return The first message in the queue
 */
COMM_MESSAGE computer_comm_rx_queue_get(void) {
	//Return the message (content of the first node)
	return(computer_comm_rx_queue.message[computer_comm_rx_queue.first]);
}

/*! Drops the first message in the queue Frees up the memory space aswell.
 */
void computer_comm_rx_queue_drop(void) {
	computer_comm_rx_queue.first++;
	
	if (computer_comm_rx_queue.first >= COMPUTER_COMM_RX_QUEUE_SIZE)
		computer_comm_rx_queue.first = 0;
  
  if (computer_comm_rx_queue.count > 0)
    computer_comm_rx_queue.count--;
}

/*! \brief Erase all content in the TX queue
 * \return The number of items that were cleared
 */
void computer_comm_rx_queue_dropall(void) {
	computer_comm_rx_queue.first = 0;
	computer_comm_rx_queue.last = 0;
  
  computer_comm_rx_queue.count = 0;
}

/*! \brief Check if the queue is empty
 *	\return 1 if the queue is empty and 0 otherwise
 */
unsigned char computer_comm_rx_queue_is_empty(void) {
	if (computer_comm_rx_queue.first == computer_comm_rx_queue.last)
		return(1);
	else
		return(0);
}

/*! \brief Check the number of message in the queue 
 *  \return The number of messages in the queue */
unsigned char computer_comm_rx_queue_count(void) {
  return(computer_comm_rx_queue.count);
}