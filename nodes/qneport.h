/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef QNEPORT_H
#define QNEPORT_H

#include <QGraphicsPathItem>

class QNEBlock;
class QNEConnection;
class GraphicElement;

class QNEPort : public QGraphicsPathItem
{
public:
  enum { Type = QGraphicsItem::UserType + 1 };
  enum { NamePort = 1, TypePort = 2 };

    QNEPort(QGraphicsItem *parent = 0);
  ~QNEPort();

  void setNEBlock(QNEBlock*);
  void setName(const QString &n);
  void setIsOutput(bool o);
  int radius();
  bool isOutput();
  QVector<QNEConnection*>& connections();
  void setPortFlags(int);

  const QString& portName() const { return name; }
  int portFlags() const { return m_portFlags; }

  int type() const { return Type; }

  QNEBlock* block() const;

  quint64 ptr();
  void setPtr(quint64);

  bool isConnected(QNEPort*);

  GraphicElement * graphicElement() const;
  void setGraphicElement(GraphicElement * graphicElement);

  void updateConnections();
    protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  private:
  QNEBlock *m_block;
  QString name;
  bool isOutput_;
  QGraphicsTextItem *label;
  int radius_;
  int margin;
  QVector<QNEConnection*> m_connections;
  int m_portFlags;
  quint64 m_ptr;

  //WPanda
  GraphicElement * m_graphicElement;
};

#endif // QNEPORT_H
