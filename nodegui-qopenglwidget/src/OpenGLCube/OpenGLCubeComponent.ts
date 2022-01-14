import {
  ComponentConfig,
  registerComponent,
} from "@nodegui/react-nodegui/dist/components/config";
import { AppContainer } from "@nodegui/react-nodegui/dist/reconciler";
import { Fiber } from "react-reconciler";
import {
  OpenGLCubeReactWidget,
  OpenGLCubeReactWidgetProps,
} from "./OpenGLCubeReactWidget";

class OpenGLCubeComponentConfig extends ComponentConfig {
  tagName = OpenGLCubeReactWidget.tagName;

  shouldSetTextContent(nextProps: OpenGLCubeReactWidgetProps): boolean {
    return true;
  }

  createInstance(
    newProps: OpenGLCubeReactWidgetProps,
    rootInstance: AppContainer,
    context: any,
    workInProgress: Fiber
  ): OpenGLCubeReactWidget {
    const widget = new OpenGLCubeReactWidget();
    widget.setProps(newProps, {});
    return widget;
  }

  commitMount(
    instance: OpenGLCubeReactWidget,
    newProps: OpenGLCubeReactWidgetProps,
    internalInstanceHandle: any
  ): void {
    if (newProps.visible !== false) {
      instance.show();
    }
    return;
  }

  finalizeInitialChildren(
    instance: OpenGLCubeReactWidget,
    newProps: OpenGLCubeReactWidgetProps,
    rootContainerInstance: AppContainer,
    context: any
  ): boolean {
    return true;
  }

  commitUpdate(
    instance: OpenGLCubeReactWidget,
    updatePayload: any,
    oldProps: OpenGLCubeReactWidgetProps,
    newProps: OpenGLCubeReactWidgetProps,
    finishedWork: Fiber
  ) {
    instance.setProps(newProps, oldProps);
  }
}

export const OpenGLCubeComponent = registerComponent<OpenGLCubeReactWidgetProps>(
  new OpenGLCubeComponentConfig()
);
