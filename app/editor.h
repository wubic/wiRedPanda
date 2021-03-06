#ifndef EDITOR_H
#define EDITOR_H

#include "icmanager.h"
#include "elementeditor.h"
#include "elementfactory.h"
#include "nodes/qneconnection.h"
#include "scene.h"
#include "simulationcontroller.h"

#include <memory>
#include <QElapsedTimer>
#include <QObject>
#include <QUndoCommand>

class IC;
class MainWindow;

class Editor : public QObject {
  Q_OBJECT
  QElapsedTimer timer;
public:
  explicit Editor( QObject *parent = nullptr );
  virtual ~Editor( );
  bool saveLocalIC( IC *ic, QString newICPath );
  bool saveLocal( QString newPath );
  void save( QDataStream &ds, const QString &dolphinFilename );
  void load( QDataStream &ds );
  void cut( const QList< QGraphicsItem* > &items, QDataStream &ds );
  void copy( const QList< QGraphicsItem* > &items, QDataStream &ds );
  void paste( QDataStream &ds );
  void selectAll( );

signals:
  void scroll( int x, int y );
  void circuitHasChanged( );

public slots:
  void clear( );
  void showWires( bool checked );
  void showGates( bool checked );
  void rotate( bool rotateRight );

  void receiveCommand( QUndoCommand *cmd );
  void copyAction( );
  void cutAction( );
  void pasteAction( );
  void deleteAction( );
  void updateTheme( );

  void mute( bool _mute = true );
private:
  QUndoStack *undoStack;
  Scene *scene;
  QList< QGraphicsItem* > itemsAt( QPointF pos );
  QGraphicsItem* itemAt( QPointF pos );
  int _editedConn_id;
  int _hoverPortElm_id;
  int _hoverPort_nbr;
  ElementEditor *_elementEditor;
  ICManager *icManager;

  bool markingSelectionIC;
  QGraphicsRectItem *selectionRect;
  QPointF selectionStartPoint;
  SimulationController *simulationController;
  QPointF mousePos, lastPos;
  void addItem( QGraphicsItem *item );
  bool draggingElement;
  QList< GraphicElement* > movedElements;
  QList< QPointF > oldPositions;
  MainWindow *mainWindow;
/*  bool mControlKeyPressed; */
  bool mShowWires;
  bool mShowGates;

  bool mousePressEvt( QGraphicsSceneMouseEvent *mouseEvt );
  bool mouseMoveEvt( QGraphicsSceneMouseEvent *mouseEvt );
  bool mouseReleaseEvt( QGraphicsSceneMouseEvent *mouseEvt );
  bool dropEvt( QGraphicsSceneDragDropEvent *dde );
  bool dragMoveEvt( QGraphicsSceneDragDropEvent *dde );
  bool wheelEvt( QWheelEvent *wEvt );

  void ctrlDrag( QPointF pos );
  void install( Scene *s );

  QNEConnection* getEditedConn( );
  void setEditedConn( QNEConnection *editedConn );

  /* QObject interface */
  void detachConnection( QNEInputPort *endPort );
  void startNewConnection( QNEOutputPort *startPort );
  void startNewConnection( QNEInputPort *endPort );

  void startSelectionRect( );

  void makeConnection( QNEConnection *editedConn );
  void redoSimulationController( );
public:
  bool eventFilter( QObject *obj, QEvent *evt );
  void setElementEditor( ElementEditor *value );
  QUndoStack* getUndoStack( ) const;
  Scene* getScene( ) const;
  void buildSelectionRect( );
  void handleHoverPort( );
  void releaseHoverPort( );

  void setHoverPort( QNEPort *port );
  QNEPort* getHoverPort( );

  void resizeScene( );
  SimulationController* getSimulationController( ) const;
  void contextMenu( QPoint screenPos );
  void updateVisibility( );
  QPointF getMousePos( ) const;


  ElementEditor* getElementEditor( ) const;

  static Editor *globalEditor;

  void deleteEditedConn( );
  void flipH( );
  void flipV( );
};

#endif /* EDITOR_H */
