/*  ps2_pal2ntsc_yfix - PS2 PAL TO NTSC VIDEO MODE CHANGER WITH Y-FIX
 *  Copyright (C) 2003-2004  Jayteemaster <jayteemaster2003@yahoo.com.br>
 *  URL: www.geocities.com/jayteemaster2003
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// CD support
void extract(char *image, char *file, char *temp_filename);
void insert(char *image, char *file, char *temp_filename);
void restore(char *image, char *file, char *temp_filename);
