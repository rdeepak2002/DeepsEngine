# svelte-nodegui-starter

**Clone and run for a quick way to see Svelte NodeGui in action.**

![logo](https://github.com/nodegui/svelte-nodegui-starter/raw/master/assets/demo.png)

## To Use

To clone and run this repository you'll need [Git](https://git-scm.com) and [Node.js](https://nodejs.org/en/download/) (which comes with [npm](http://npmjs.com)) installed on your computer.

Make sure you have met the requirements listed here: https://docs.nodegui.org/#/tutorial/development-environment

From your command line:

```bash
# Copy files from starter repo into a directory called "my-project"
npx degit https://github.com/nodegui/svelte-nodegui-starter my-project
# Go into the repository
cd my-project
# remove old folders
rm -rf dist
rm -rf node_modules
# Install dependencies
arch -x86_64 npm install
# Build the app in development mode (unminified; watch mode on)
arch -x86_64 npm run dev
# (From another terminal) Run the built app
arch -x86_64 npm run start
```

## Resources for Learning NodeGui

- [svelte.nodegui.org](https://svelte.nodegui.org) - all of Svelte NodeGui's documentation

## Packaging app as a distributable

In order to distribute your finished app, you can use [@nodegui/packer](https://github.com/nodegui/packer)

### Step 1: (_**Run this command only once**_)

```sh
npx nodegui-packer --init MyAppName
```

This will produce the deploy directory containing the template. You can modify this to suite your needs. Like add icons, change the name, description and add other native features or dependencies. Make sure you commit this directory.

### Step 2: (_**Run this command every time you want to build a new distributable**_)

Next you can run the pack command:

```sh
npm run build
```

This will produce the js bundle along with assets inside the `./dist` directory

```sh
npx nodegui-packer --pack ./dist
```

This will build the distributable using `@nodegui/packer` based on your template. The output of the command is found under the build directory. You should gitignore the build directory.

More details about `@nodegui/packer` can be found here: https://github.com/nodegui/packer

## License

MIT
