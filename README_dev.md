# 開発者・出題者用
## 問題ファイルの作り方
\# が説明です。実際のファイルには\# は入れないでください。
```json
{
  "core_num": 3, # デフォルトのコア数
  "edges": [     # エッジ設定
    {
      "src": 1,  # 入口のidx
      "dst": 0   # 出口のidx
    }
  ],
  "nodes": [     # ノード設定
    {
      "idx": 0,  # エッジで使うidx
      "wcet": 2, # 実行時間
      "x": 0,    # GUI上のX座標（左が0）
      "y": 1     # GUI上のY座標（上が0）
    }
  ]
}
```
## 開発を行う場合
デバッグ環境がないと動かしながらコード修正をすることができません。
少し面倒ですが、以下のどちらかの手順で環境構築をしてください。

### 1. gitに慣れている人向け（こっちの方が便利）
1. Visual Studio をインストール
2. [Siv3d](https://siv3d.github.io/ja-jp/) をインストール
3. `HowToDAGScheduling`という名前のプロジェクトをOpenSiv3dのテンプレートで作成（公式ページも参照）
4. `HowToDAGScheduling/`に移動して以下のコマンドを実行
```shell
git init
git remote add origin git@github.com:rokamu623/HowToDAGScheduling.git
```
5. 以下のファイルを削除
  - HowToDAGScheduling/App/Resource.rc
  - HowToDAGScheduling/App/icon.ico
  - HowToDAGScheduling/Main.cpp
6. 以下のコマンドを実行
```shell
git pull origin main
```
7. NASから`BGM/`、`SE/`を`HowToDAGScheduling/App/`下に移動する
8. HowToDAGScheduling.slnを開く
9. ソリューションエクスプローラのHeader Filesを右クリック→既存の項目を追加 から、全ての.hファイルを選択して追加する
10. ソリューションエクスプローラのSource Filesを右クリック→既存の項目を追加 から、全ての.cppファイルを選択して追加する
11. Ctrl+F5で動作を確認

### 2. gitに慣れていない人向け
1. Visual Studio をインストール
2. [Siv3d](https://siv3d.github.io/ja-jp/) をインストール
3. `HowToDAGScheduling`という名前のプロジェクトをOpenSiv3dのテンプレートで作成（公式ページも参照）
4. `HowToDAGScheduling`と別の箇所にgit cloneやNASからのコピーでソースコードを持ってくる
5. `.hファイル`、`.cppファイル`を`HowToDAGScheduling/HowToDAGScheduling/`下に移動する（main.cppと同じディレクトリ）
6. `BGM/`、`SE/`を`HowToDAGScheduling/App/`下に移動する
7. HowToDAGScheduling.slnを開く
8. ソリューションエクスプローラのHeader Filesを右クリック→既存の項目を追加 から、全ての.hファイルを選択して追加する
9. ソリューションエクスプローラのSource Filesを右クリック→既存の項目を追加 から、全ての.cppファイルを選択して追加する
10. Ctrl+F5で動作を確認
11. 変更したファイルは4.で作ったディレクトリに送りなおしてそこからgithubに送る
