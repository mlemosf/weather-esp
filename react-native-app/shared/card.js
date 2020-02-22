import React from 'react';
import { StyleSheet, Text, View } from 'react-native';

const Card = ({props}) => {
	return(
		<View style={styles.card}>
			<Text style={styles.cardLeft}>{ props.key }</Text>
			<Text style={styles.cardRight}>{ props.value } { props.scale }</Text>

		</View>
	);
}

const styles = StyleSheet.create({
	card: {
		borderRadius: 10,
		elevation: 5,
		backgroundColor: "#333",
		shadowOffset: {
			widht: 6,
			height: 6,
		},
		shadowColor: "#333",
		shadowOpacity: 0.3,
		shadowRadius: 2,
		marginHorizontal: 5,
		marginVertical: 5,
		flexDirection: "row",
		flexWrap: "wrap"
	},
	cardLeft: {
		fontSize: 30,
		color: "#fff",
		paddingTop: 10,
		paddingLeft: 10
	},
	cardRight: {
		fontSize: 60,
		color: "#fff",
		paddingLeft: 20,
		alignSelf: "flex-end"
	}
});

export default Card;
