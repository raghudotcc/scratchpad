import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';

export function activate(context: vscode.ExtensionContext) {
	const provider = new IncludeCompletionProvider();
	context.subscriptions.push(vscode.languages.registerCompletionItemProvider('markdown', provider, '['));
}



class IncludeCompletionProvider implements vscode.CompletionItemProvider, vscode.Disposable {
	private titles: string[] = [];
	private watcher: vscode.FileSystemWatcher;
	
	constructor() {
		this.updateTitles();

		this.watcher = vscode.workspace.createFileSystemWatcher("**/_site/autocomplete.txt");
		this.watcher.onDidCreate(()=> this.updateTitles());
		this.watcher.onDidChange(()=> this.updateTitles());
		this.watcher.onDidDelete(()=> this.updateTitles());
	}

	public dispose() {
		this.watcher.dispose();
	}

	public provideCompletionItems (document: vscode.TextDocument, position: vscode.Position, token: vscode.CancellationToken) {
		let linePrefix = document.lineAt(position).text.substr(0, position.character);
		if (!linePrefix.endsWith('[[')) {
				return undefined;
		}

		let completionItemArray: vscode.CompletionItem[] = [];

		for (let entry of this.titles) {
			completionItemArray.push(new vscode.CompletionItem(entry, vscode.CompletionItemKind.Text));
		}

		return completionItemArray;
	}

	private async updateTitles() {
		if (!vscode.workspace.workspaceFolders) {
			return undefined;
		}

		const folderUri = vscode.workspace.workspaceFolders[0].uri;
		const fileUri = folderUri.with({ path: path.posix.join(folderUri.path, '_site/autocomplete.txt') });

		let titles = <string[]> undefined;

		const readData =  await vscode.workspace.fs.readFile(fileUri);
		titles = Buffer.from(readData).toString('utf8').split(";");

		this.titles = titles;
	}


}

