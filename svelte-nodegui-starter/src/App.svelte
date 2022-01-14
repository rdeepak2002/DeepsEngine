<script lang="ts">
    import { onMount } from 'svelte';
    import { QIcon } from "@nodegui/nodegui";
    import StepOne from "./components/StepOne.svelte";
    import StepTwo from "./components/StepTwo.svelte";
    import nodeguiIcon from "../assets/nodegui.jpg";
    import type { NSVElement, RNWindow } from "@nodegui/svelte-nodegui";
    import path from "path";

    // interface coreInterface {
    //     checkEngineStatus: (status: number) => string
    // }

    const core = require('../../engine/build/Release/core.node');
    const blankProjectPath = path.resolve(path.join("example_projects", "blank_project"));

    console.log('starting renderer...');
    console.log(core.checkEngineStatus(1));
    core.createRenderer(true, true, blankProjectPath);
    core.updateRenderer();

    const winIcon = new QIcon(nodeguiIcon);

    /**
     * The exact type for this is: NSVElement<RNWindow>
     * ... However, the Svelte language tools erroneously expect all bind:this values to extend HTMLElement, so
     * for now, we have to rely on reasserting the type.
     */
    let win;

    onMount(() => {
        (window as any).win = win; // Prevent garbage collection, otherwise the window quickly disappears!
        (win as NSVElement<RNWindow>).nativeView.show();

        return () => {
            delete (window as any).win;
        };
    });
</script>

<window
    bind:this={win}
    windowIcon={winIcon}
    minSize={{ width: 500, height: 520 }}
    windowTitle="Deeps Engine"
>
    <view style="flex: 1;">
        <text>Hello World1</text>
<!--        <button on:click={startRenderer}>start renderer</button>-->
    </view>
</window>

<style>

</style>
