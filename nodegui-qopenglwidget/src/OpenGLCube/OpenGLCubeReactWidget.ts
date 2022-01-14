import { NodeWidget } from "@nodegui/nodegui";
import { RNWidget } from "@nodegui/react-nodegui/dist/components/config";
import {
  setViewProps,
  ViewProps,
} from "@nodegui/react-nodegui/dist/components/View/RNView";
import { throwUnsupported } from "@nodegui/react-nodegui/dist/utils/helpers";
import { OpenGLCubeWidget, OpenGLCubeWidgetSignals } from "./OpenGLCubeWidget";

type OpenGLCubeReactWidgetChildren = string | number | Array<string | number>;

export interface OpenGLCubeReactWidgetProps
  extends ViewProps<OpenGLCubeWidgetSignals> {
  children?: OpenGLCubeReactWidgetChildren;
}

export const setOpenGLCubeProps = (
  widget: OpenGLCubeReactWidget,
  newProps: OpenGLCubeReactWidgetProps,
  oldProps: OpenGLCubeReactWidgetProps
) => {
  const setter: OpenGLCubeReactWidgetProps = {
    set children(_: OpenGLCubeReactWidgetChildren) {
      throw new Error("Setting children is not allowed");
    },
  };
  Object.assign(setter, newProps);
  setViewProps(widget, newProps, oldProps);
};

export class OpenGLCubeReactWidget
  extends OpenGLCubeWidget
  implements RNWidget {
  setProps(
    newProps: OpenGLCubeReactWidgetProps,
    oldProps: OpenGLCubeReactWidgetProps
  ): void {
    setOpenGLCubeProps(this, newProps, oldProps);
  }

  appendInitialChild(child: NodeWidget<any>) {
    throwUnsupported(this);
  }

  appendChild(child: NodeWidget<any>): void {
    throwUnsupported(this);
  }

  insertBefore(child: NodeWidget<any>, beforeChild: NodeWidget<any>): void {
    throwUnsupported(this);
  }

  removeChild(child: NodeWidget<any>): void {
    throwUnsupported(this);
  }

  static tagName = "OpenGLCube";
}
