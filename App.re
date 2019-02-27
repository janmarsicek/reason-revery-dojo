open Revery;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

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

  let createElement = (~children as _, ~story, ()) =>
    component(hooks => {
      let storyStyle =
        Style.[padding(10), border(~color=Colors.white, ~width=1)];

      let contentStyle =
        Style.[fontFamily("Roboto-Regular.ttf"), fontSize(12)];
      (
        hooks,
        <View style=storyStyle>
          <View>
            <Text style=headerStyle text={StoryDao.view_title(story)} />
          </View>
          <View>
            <Text style=headerStyle text={StoryDao.view_by(story)} />
          </View>
          <View>
            <Text
              style=headerStyle
              text={string_of_int(StoryDao.view_score(story))}
            />
          </View>
          <View>
            <Text
              style=headerStyle
              text={string_of_int(StoryDao.view_time(story))}
            />
          </View>
          {renderUrl(StoryDao.view_url(story))}
        </View>,
      );
    });
};

module StoryList = {
  let component = React.component("StoryList");

  let createElement = (~children as _, ()) =>
    component(hooks => {
      let (stories, setStories, hooks) =
        React.Hooks.state(StoryDao.fetchTopStories(), hooks);
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
