import {
  ComponentConfig,
  registerComponent,
} from "@nodegui/react-nodegui/dist/components/config";
import { AppContainer } from "@nodegui/react-nodegui/dist/reconciler";
import { Fiber } from "react-reconciler";
import {
  OpenGLReactWidget,
  OpenGLCubeReactWidgetProps,
} from "./OpenGLReactWidget";

class OpenGLCubeComponentConfig extends ComponentConfig {
  tagName = OpenGLReactWidget.tagName;

  shouldSetTextContent(nextProps: OpenGLCubeReactWidgetProps): boolean {
    return true;
  }

  createInstance(
    newProps: OpenGLCubeReactWidgetProps,
    rootInstance: AppContainer,
    context: any,
    workInProgress: Fiber
  ): OpenGLReactWidget {
    const widget = new OpenGLReactWidget();
    widget.setProps(newProps, {});
    return widget;
  }

  commitMount(
    instance: OpenGLReactWidget,
    newProps: OpenGLCubeReactWidgetProps,
    internalInstanceHandle: any
  ): void {
    if (newProps.visible !== false) {
      instance.show();
    }
    return;
  }

  finalizeInitialChildren(
    instance: OpenGLReactWidget,
    newProps: OpenGLCubeReactWidgetProps,
    rootContainerInstance: AppContainer,
    context: any
  ): boolean {
    return true;
  }

  commitUpdate(
    instance: OpenGLReactWidget,
    updatePayload: any,
    oldProps: OpenGLCubeReactWidgetProps,
    newProps: OpenGLCubeReactWidgetProps,
    finishedWork: Fiber
  ) {
    instance.setProps(newProps, oldProps);
  }
}

export const OpenGLComponent = registerComponent<OpenGLCubeReactWidgetProps>(
  new OpenGLCubeComponentConfig()
);
