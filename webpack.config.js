const HtmlWebPackPlugin = require("html-webpack-plugin");
const CompressionPlugin = require("compression-webpack-plugin");
const BrotliPlugin = require('brotli-webpack-plugin');
module.exports = {
  module: {
    rules: [
      {
        test: /\.(js|jsx)$/,
        exclude: /node_modules/,
        use: {
          loader: "babel-loader"
        }
      },
      {
        test: /\.(html|htm)$/,
        use: [
          {
            loader: "html-loader"
          }
        ]
      }
    ]
  },
  plugins: [
    new HtmlWebPackPlugin({
      template: "./src/index.html",
      filename: "./index.html"
    }),
    new CompressionPlugin({
        filename: '[path].gz[query]',
        algorithm: 'gzip',
        test: /\.(js|jsx)$|\.css$|\.(html|htm)$/,
        threshold: 10240,
        minRatio: 0.7
    }),
    new BrotliPlugin({
        asset: '[path].br[query]',
        test: /\.(js|jsx)$|\.css|\.(html|htm)$/,
        threshold: 10240,
        minRatio: 0.7
    })
  ]
};
