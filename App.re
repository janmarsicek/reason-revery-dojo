open Revery;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

// type view = {
//   by: string,
//   id: int,
//   score: int,
//   time: int,
//   title: string,
//   url: option(string),
// };

// module StoryDao = {
//   open Yojson.Basic.Util;

//   type view = {
//     by: string,
//     id: int,
//     score: int,
//     time: int,
//     title: string,
//     url: option(string),
//   };

//   type t = view;

//   let fetchTopStories = () => {
//     let json = Yojson.Basic.from_file("./stories.json");
//     json
//     |> to_list
//     |> List.map(storyDetail =>
//          {
//            by: member("by", storyDetail) |> to_string,
//            id: member("id", storyDetail) |> to_int,
//            title: member("title", storyDetail) |> to_string,
//            score: member("score", storyDetail) |> to_int,
//            time: member("time", storyDetail) |> to_int,
//            url: member("url", storyDetail) |> to_string_option,
//          }
//        );
//   };

//   let view_title = story => story.title;
//   let view_by = story => story.by;
//   let view_id = story => story.id;
//   let view_time = story => story.time;
//   let view_url = story => story.url;
//   let view_score = story => story.score;
// };

module Story = {
  let component = React.component("Story");
  let headerStyle = Style.[fontFamily("Roboto-Regular.ttf"), fontSize(18)];
  let renderUrl = (url: option(string)) =>
    switch (url) {
    | Some("tst") =>
      <View> <Text style=headerStyle text="my custom switch case" /> </View>
    | Some(s) => <View> <Text style=headerStyle text=s /> </View>
    | None => <View />
    };

  let createElement = (~children as _, ~story: StoryDao.t, ()) =>
    component(hooks => {
      let storyStyle =
        Style.[padding(10), border(~color=Colors.white, ~width=1)];

      let contentStyle =
        Style.[fontFamily("Roboto-Regular.ttf"), fontSize(12)];
      (
        hooks,
        <View style=storyStyle>
          <View> <Text style=headerStyle text={story.title} /> </View>
          <View> <Text style=headerStyle text={story.by} /> </View>
          <View>
            <Text style=headerStyle text={string_of_int(story.score)} />
          </View>
          <View>
            <Text style=headerStyle text={string_of_int(story.time)} />
          </View>
          {renderUrl(story.url)}
        </View>,
      );
    });
};

let mockData: list(StoryDao.t) = [
  {title: "Title1", by: "Someone", id: 1, score: 10, time: 1, url: None},
  {
    title: "Title2",
    by: "Someone 2",
    id: 2,
    score: 16,
    time: 10,
    url: Some("https://github.com/romanschejbal/electron-blog"),
  },
  {
    title: "Title3",
    by: "Someone 3",
    id: 3,
    score: 14,
    time: 100,
    url: Some("tst"),
  },
  {title: "Title4", by: "Someone 4", id: 4, score: 13, time: 1000, url: None},
  {
    title: "Title5",
    by: "Someone 5",
    id: 5,
    score: 17,
    time: 10000,
    url: None,
  },
];

module StoryList = {
  let component = React.component("StoryList");

  let createElement = (~children as _, ()) =>
    component(hooks => {
      let (stories, setStories, hooks) = React.Hooks.state(mockData, hooks);
      let hooks =
        React.Hooks.effect(
          OnMount,
          () => Some(() => print_endline("Unmount")),
          hooks,
        );

      let textHeaderStyle =
        Style.[
          color(Colors.white),
          fontFamily("Roboto-Regular.ttf"),
          fontSize(24),
          marginHorizontal(8),
        ];

      (
        hooks,
        <View>
          <Text text="Stories" style=textHeaderStyle />
          {React.listToElement(List.map(story => <Story story />, stories))}
        </View>,
      );
    });
};

let init = app => {
  let win = App.createWindow(app, "Welcome to Revery!");

  let containerStyle =
    Style.[
      position(`Absolute),
      justifyContent(`FlexStart),
      alignItems(`Center),
      bottom(0),
      top(0),
      left(0),
      right(0),
      backgroundColor(Colors.black),
    ];

  let scrollViewStyle =
    Style.[height(400), width(450), border(~width=1, ~color=Colors.red)];

  let render = () =>
    <View style=containerStyle>
      <ScrollView style=scrollViewStyle> <StoryList /> </ScrollView>
    </View>;

  UI.start(win, render);
};

App.start(init);

App.start(init);

App.start(init);

App.start(init);
