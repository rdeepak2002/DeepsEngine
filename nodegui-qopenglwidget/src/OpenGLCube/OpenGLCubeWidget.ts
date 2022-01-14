import { OpenGLCube } from "@native/OpenGLCube.node";
import { NativeElement, NodeWidget } from "@nodegui/nodegui";
import { QOpenGLWidgetSignals } from "@nodegui/nodegui/dist/lib/QtWidgets/QOpenGLWidget";

export interface OpenGLCubeWidgetSignals extends QOpenGLWidgetSignals {}

export class OpenGLCubeWidget extends NodeWidget<OpenGLCubeWidgetSignals> {
  native: NativeElement;

  constructor(parent?: NodeWidget<any>) {
    let native;
    if (parent) {
      native = new OpenGLCube(parent.native);
    } else {
      native = new OpenGLCube();
    }
    super(native);
    this.native = native;
    this.nodeParent = parent;
  }

  test() {
    return this.native.test();
  }
}
