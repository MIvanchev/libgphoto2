/*
 * Small jpeg decoder library (header file)
 *
 * *** NOTE: This is a modified version to deal with the ax203 "JPEG" fmt
 * *** This version can not decompress regular JPEG files, see
 * *** README.ax203-compression for details
 *
 * Copyright (c) 2006, Luc Saillard <luc@saillard.org>
 *
 * ax203 modifications:
 * Copyright (c) 2010, Hans de Goede <hdegoede@redhat.com>
 *
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 * - Neither the name of the author nor the names of its contributors may be
 *  used to endorse or promote products derived from this software without
 *  specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef CAMLIBS_AX203_TINYJPEG_H
#define CAMLIBS_AX203_TINYJPEG_H

#ifdef __cplusplus
extern "C" {
#endif

struct jdec_private;

struct jdec_private *ax203_tinyjpeg_init(void);
void ax203_tinyjpeg_free(struct jdec_private *priv);

int ax203_tinyjpeg_parse_header(struct jdec_private *priv, const unsigned char *buf, unsigned int size);
int ax203_tinyjpeg_decode(struct jdec_private *priv);
const char *ax203_tinyjpeg_get_errorstring(struct jdec_private *priv);
void ax203_tinyjpeg_get_size(struct jdec_private *priv, unsigned int *width, unsigned int *height);
int ax203_tinyjpeg_get_components(struct jdec_private *priv, unsigned char **components);
int ax203_tinyjpeg_set_components(struct jdec_private *priv, unsigned char **components, unsigned int ncomponents);

#ifdef __cplusplus
}
#endif

#endif /* !defined(CAMLIBS_AX203_TINYJPEG_H) */



